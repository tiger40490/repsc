#include "Parser.h"
#include "MsgParser.h"

#include "OrderMsg.h"
#include "PacketHeader.h"
#include "utils.h"

#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

/////////////// static data members 
std::ofstream Parser::file;
std::map<char, MsgParser*> Parser::workers;
std::unordered_map<uint32_t, Order> Parser::orders;
std::map<std::string, map<std::string, int64_t>> Parser::actionRecorder;

static void countWrites(size_t sz){ //This function Can't be part of w2f since each template instantiation of w2f has a separate allocation of static local variables
    static int cnt=0; ++cnt;
    static int len=0; len += sz;
    static vector<uint8_t> sizes; sizes.push_back(sz);
    cout<<cnt<<" events written to file. Write sizes are : ";
    for (auto const & i : sizes) cout<<(int)i<<" ";
    cout<<len<<" is the total length\n"; 
}
template<class E> void Parser::w2f(E const* ev){
    file.write(reinterpret_cast<char const*>(ev), sizeof(E));
    countWrites(sizeof(E));
}
char Parser::record(std::string actionId, int64_t val, std::string stock ){
  if (Parser::actionRecorder.count(actionId) ){
     //throw string( "actionId should be globally unique" );
     assert(Parser::actionRecorder[actionId].count(stock) ==0 && "Programmer error.. repeated actionId for the same stock, However, this is part of test fixture, not for production error reporting, so we should  NOT throw exception." );
     return 'r';  //repeat
  }
  Parser::actionRecorder[actionId][stock] = val;
  //cout<<val<<" recorded against "<<stock<<actionId<<endl;
  return 0; 
}
char Parser::check(std::string actionId, int64_t exp, std::string stock){
  //cout<<"checking "<<actionId<<endl;
  if (Parser::actionRecorder.count(actionId) == 0) return 'e'  ; //no such event id in recorder
  if (Parser::actionRecorder[actionId].count(stock) == 0) return 's'; // no such stock
  if (Parser::actionRecorder[actionId][stock] != exp ) return 'u' ;  // values unequal
  cout<<"  :) "<<exp<<" verified against "<<actionId<<" / "<<stock<<endl;
  return 0;
}

Parser::Parser(int date, const std::string &outputFilename) {
  this->file = ofstream(outputFilename, std::ofstream::out);
  if (workers.empty()){
    workers['A'] = new AddOrderParser();
    workers['E'] = new ExeOrderParser();
    workers['X'] = new DecOrderParser();
    workers['R'] = new RepOrderParser();
  }
}

char Parser::readPayload( char *buf, size_t len) {
  cout<<len<<" ===== len in readPayload()"<<endl;
  //dumpBuffer(buf, len);
  for (int cnt=1; ; ++cnt){
    char const msgType = buf[0];
//    cout<<msgType<<" = msgType found in first byte of # "<<cnt<<" message in this pkt\n";
    MsgParser * worker = Parser::workers[msgType];
    if (worker == nullptr){
      cerr<<(int)msgType<<" is invalid msgType"<<endl;
      return 'i';
    }
    if (len >= worker->msgSz){
      worker->parse(buf); //return value should be 0 but if not nothing can be done
      if (len > worker->msgSz){
          len -= worker->msgSz;
          buf += worker->msgSz;
          //cout<<len<<" = len after processing "<<cnt<<" messages in this pkt\n";
          continue;
      }
      assert (len == worker->msgSz);
      cout<<cnt<<" messages parsed and payload is exhausted. Now looking for next payload in warehouse.."<<endl;
      return 0;
    }else{ 
      return 'p'; //todo save the partial msg
    }
  }    
}
void Parser::onUDPPacket(const char *buf, size_t len) {
  static deque<vector<char>> wh;
  static int64_t whLowSeq; //wh[ 999-lowSeq ] is a vector holding payload of packet #999

  size_t const len2 = len;
  //dumpBuffer(buf, len, "into onUDP");
  auto hdr = cast<PacketHeader>(const_cast<char*>(buf));
  //dumpBuffer(buf, len, "after reinterpret_cast, showing in-place endianness conversion");

  if (len != hdr->sz){
      cerr<<"Size value in header differs from buffer length... corrupted buffer, to be discarded."<<endl; return; //no updateSeq()
  }
  size_t const PKT_HDR_SZ = sizeof(PacketHeader);
  if (len < PKT_HDR_SZ){
      cerr<<"buffer too short ... corrupted buffer, to be discarded."<<endl; return; //no updateSeq()
  }
  auto const seq = hdr->seq;
  if (seq < this->expectedSeq){
    cout<<"Header seq above is a dupe .. dropped"<<endl; return; //no updateSeq()
  }

  if (seq > this->expectedSeq){ // 
    cout<<"warehousing "<<seq<<" # current whLowSeq = "<<whLowSeq <<endl;
    auto whHiSeq = whLowSeq + wh.size() -1 ;
    if (wh.empty()){ 
        wh.push_back( vector<char>(buf + PKT_HDR_SZ, buf + len));
        whLowSeq = seq; cout<<seq<<" is the newly added payload seq in an empty warehouse.";
    }else if (seq < whLowSeq ) {
          for (auto next2fill = whLowSeq-1; next2fill >= seq; --next2fill){
            wh.push_front(vector<char>());
            cout<<next2fill<<" <-- This pkt seq has not arrived but a dummy pkt is saved in warehouse\n";
          }
          whLowSeq = seq;
    }else if (whHiSeq < seq) {
          for (auto next2fill = whHiSeq+1; next2fill <= seq; ++next2fill){
            wh.push_back(vector<char>());
            cout<<next2fill<<" <-- This pkt seq has not arrived but a dummy pkt is saved in warehouse\n";
          }
          assert(whLowSeq + wh.size()-1 == seq);
    }
    assert ( whLowSeq <= seq && seq < whLowSeq + wh.size());
    wh[seq-whLowSeq] = vector<char>(buf + PKT_HDR_SZ, buf + len);
    char const * saved = wh[seq-whLowSeq].data();
    dumpBuffer(saved, len-PKT_HDR_SZ, "just warehoused ");
    return; //no updateSeq()
  }
  assert (seq == this->expectedSeq );
  cout<<"Header seq above is The Expected .. now processing payload"<<endl;
  if (len == PKT_HDR_SZ ){ cout<<"dummy packet .. taken as a heartbeat"<<endl; 
    updateSeq(seq); 
    return;
  }
  assert(len > PKT_HDR_SZ ); 
  readPayload(const_cast<char*>(buf)+PKT_HDR_SZ,  len-PKT_HDR_SZ);
  updateSeq(seq); 
  for(;/*idx < wh.size() && wh[idx].size()*/;){
    int idx = this->expectedSeq - whLowSeq;
    if (idx < 0) break;
    if (idx >= (int) wh.size()) break;
    if (wh[idx].empty()) break; //dummy payload
    char * payload = wh[idx].data();
    cout<<this->expectedSeq<<" <-- The payload with this seq now located in warehouse.. parsing..\n";
    readPayload(payload, wh[idx].size());
    updateSeq(); 
    size_t const outdatedCnt = this->expectedSeq - whLowSeq; 
    cout<<"Freeing memory by releasing  "<<outdatedCnt<< "  outdated payloads from warehouse..\n";
    for (size_t popped=0; popped < outdatedCnt; ++popped){
      wh.pop_front(); //std::vector would destroy the underlying array on heap, freeing up memory
    }
    whLowSeq = this->expectedSeq;
    cout<<whLowSeq<<" is the now the Lowest Seq in warehouse\n";
  }
  return;
}
