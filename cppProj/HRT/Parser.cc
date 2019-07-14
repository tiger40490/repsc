#include "Parser.h"
#include "MsgParser.h"
#include "AddOrderParser.h"
#include "RepOrderParser.h"
#include "DecOrderParser.h"
#include "ExeOrderParser.h"

#include "messages.h"
#include "PacketHeader.h"
#include "utils.h"

#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

// v v v v   static data members   v v v v  
std::ofstream Parser::file;
std::map<char, MsgParser*> Parser::workers;
std::unordered_map<uint32_t, Order> Parser::orders;
std::map<std::string, map<std::string, int64_t>> Parser::actionRecorder;
// v v v v   action recorder, for dev testing   v v v v  
char Parser::record(std::string actionId, int64_t val, std::string stock ){
  if (actionRecorder.count(actionId) ){
     assert(actionRecorder[actionId].count(stock) ==0 && "Programmer error.. repeated actionId for the same stock, However, this is part of test fixture, not for production error reporting, so we should  NOT throw exception." );
     return 'r';  //repeat
  }
  actionRecorder[actionId][stock] = val;
  ss1<<val<<" recorded against "<<stock<<actionId<<endl;
  return 0; 
}
char Parser::check(std::string actionId, int64_t exp, std::string stock){
  if (actionRecorder.count(actionId) == 0) return 'e'  ; //no such event id in recorder
  if (actionRecorder[actionId].count(stock) == 0) return 's'; // no such stock
  if (actionRecorder[actionId][stock] != exp ) return 'u' ;  // values unequal
  cout<<"  :) "<<exp<<" verified against "<<actionId<<" / "<<stock<<endl;
  return 0;
}
// v v v v    writing events to file   v v v v  
static void countWrites(size_t const sz){ //This function Can't be part of w2f since each template instantiation of w2f has a separate allocation of static local variables
    static int cnt=0; ++cnt;
    static int len=0; len += sz;
    static vector<uint8_t> sizes; sizes.push_back(sz);
    ss3<<cnt<<" events written to file. Write sizes are : ";
    for (auto const & i : sizes) cout<<(int)i<<" ";
    ss3<<len<<" <-- last length is the total length.. should match file size\n"; 
}
template<class E> void Parser::w2f(E const* ev){
    file.write(reinterpret_cast<char const*>(ev), sizeof(E));
    countWrites(sizeof(E));
}
// v v v v    ctor   v v v v  
Parser::Parser(int date, const std::string &outputFilename) {
  this->file = ofstream(outputFilename, std::ofstream::out);
  if (workers.empty()){
    workers['A'] = new AddOrderParser();
    workers['E'] = new ExeOrderParser();
    workers['X'] = new DecOrderParser();
    workers['R'] = new RepOrderParser();
  }
}
// v v v v    packet parsing logic   v v v v  
char Parser::readPayload( char *buf, size_t len) {
  ss2<<len<<" ===== len in readPayload()"<<endl;
  for (size_t cnt=1; ; ++cnt){
      char const msgType = buf[0]; MsgParser* worker = Parser::workers[msgType];
      if (worker == nullptr){ return 'i'; }
  //      cerr<<(int)msgType<<" is invalid msgType"<<endl;

      if (len < worker->msgSz) return 'p'; //partial msg

      int status = worker->parse(buf); ss1<<"Message parsed, and return code is "<<status<<endl;

      if (len > worker->msgSz){
          len -= worker->msgSz;
          buf += worker->msgSz;
          ss1<<len<<" = len after processing "<<cnt<<" messages in this pkt\n";
          continue;
      }
      assert (len == worker->msgSz);
      ss2<<cnt<<" messages parsed, and payload exhausted. Now looking for next payload in warehouse.."<<endl;
      return 0;
  }    
}
void Parser::onUDPPacket(const char *buf, size_t len) {
  static deque<vector<char>> wh;
  static int64_t whLowSeq; //wh[ 999-lowSeq ] is a vector holding payload of packet #999

  size_t const len2 = len;
  dumpBuffer(buf, len, "into onUDP", 1);
  auto hdr = cast<PacketHeader>(const_cast<char*>(buf));
  dumpBuffer(buf, len, "after reinterpret_cast, showing in-place endianness conversion",1);

  if (len != hdr->sz){
      cerr<<"Size value in header differs from buffer length... corrupted buffer, to be discarded."<<endl; 
      return; //no updateSeq()
  }
  size_t const PKT_HDR_SZ = sizeof(PacketHeader);
  if (len < PKT_HDR_SZ){
      cerr<<"buffer too short ... corrupted buffer, to be discarded."<<endl; 
      return; //no updateSeq()
  }
  auto const seq = hdr->seq;
  if (seq < this->expectedSeq){
    cout<<"Header seq above is a dupe .. dropped"<<endl; 
    return; //no updateSeq()
  }

  if (seq > this->expectedSeq){ // 
    cout<<"warehousing "<<seq<<" , while current whLowSeq = "<<whLowSeq <<endl;
    auto whHiSeq = whLowSeq + wh.size() -1 ;
    if (wh.empty()){ 
        wh.push_back( vector<char>(buf + PKT_HDR_SZ, buf + len));
        whLowSeq = seq; ss3<<seq<<" is the newly added payload seq in an empty warehouse.";
    }else if (seq < whLowSeq ) {
        for (auto next2fill = whLowSeq-1; next2fill >= seq; --next2fill){
            wh.push_front(vector<char>());
            ss2<<next2fill<<" <-- This pkt seq has not arrived but a dummy pkt is saved in warehouse\n";
        }
          whLowSeq = seq;
    }else if (whHiSeq < seq) {
        for (auto next2fill = whHiSeq+1; next2fill <= seq; ++next2fill){
            wh.push_back(vector<char>());
            ss2<<next2fill<<" <-- This pkt seq has not arrived but a dummy pkt is saved in warehouse\n";
        }
        assert(whLowSeq + wh.size()-1 == seq);
    }
    assert ( whLowSeq <= seq && seq < whLowSeq + wh.size());
    wh[seq-whLowSeq] = vector<char>(buf + PKT_HDR_SZ, buf + len);
    char const * saved = wh[seq-whLowSeq].data();
    dumpBuffer(saved, len-PKT_HDR_SZ, "just warehoused", 1);
    return; //no updateSeq()
  }
  assert (seq == this->expectedSeq );
  ss2<<"Header seq above is The Expected .. now processing payload"<<endl;
  if (len == PKT_HDR_SZ ){
    ss1<<"dummy packet .. taken as a heartbeat"<<endl; 
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
