#include "Parser.h"
#include "PacketHeader.h"
#include "OrderMsg.h"
#include "MsgParser.h"

#include "utils.h"
#include "Order.h"
#include "BaseEvent.h"

#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <cassert>
using namespace std;


/////////// now the static fields and other members of Parser class
ofstream Parser::file;
std::map<char, MsgParser*> Parser::workers;
std::unordered_map<uint32_t, Order> Parser::orders;
std::map<std::string, map<std::string, uint64_t>> Parser::eventRecorder;

void countWrites(size_t sz){ //Can't be part of w2f since each template instantiation of w2f has a separate allocation of static local variables
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
char Parser::record(std::string eventId, uint64_t val, std::string stock ){
  if (Parser::eventRecorder.count(eventId) ){
     //throw string( "eventId should be globally unique" );
     assert(Parser::eventRecorder[eventId].count(stock) ==0 && "Programmer error.. repeated eventId for the same stock, However, this is part of test fixture, not for production error reporting, so we should  NOT throw exception." );
     return 'r';  //repeat
  }
  Parser::eventRecorder[eventId][stock] = val;
  cout<<val<<" recorded against "<<eventId<<endl;
  return 0; 
}
char Parser::check(std::string eventId, uint64_t exp, std::string stock){
  if (Parser::eventRecorder.count(eventId) == 0) return 'e'  ; //no such event id in recorder
  if (Parser::eventRecorder[eventId].count(stock) == 0) return 's'; // no such stock
  if (Parser::eventRecorder[eventId][stock] != exp ) return 'u' ;  // values unequal
  cout<<"  :) "<<exp<<" verified against "<<eventId<<" / "<<stock<<endl;
  return 0;
}

Parser::Parser(int date, const std::string &outputFilename) {
  file = ofstream(to_string(date)+".out", std::ofstream::out);
  if (workers.empty()){
    workers['A'] = new AddOrderParser();
    workers['E'] = new ExeOrderParser();
    workers['X'] = new DecOrderParser();
    workers['R'] = new RepOrderParser();
  }
}

char Parser::readPayload( char *buf, size_t len) {
  cout<<len<<" = len in readPayload()"<<endl;
  dumpBuffer(buf, len);
  for (int cnt=1; ; ++cnt){
      //check msg type then remaining size
    char const msgType = buf[0];
    MsgParser * worker = Parser::workers[msgType];
    if (worker == nullptr){
      cerr<<msgType<<" is invalid msgType"<<endl;
      return 'i';
    }
    if (len >= worker->msgSz){
      worker->parse(buf);
      //if (len == worker->msgSz){
      if (len > worker->msgSz){
          len -= worker->msgSz;
          continue;
      }
      assert (len == worker->msgSz);
//      cout<<cnt<<" messages parsed and packet is exhausted"<<endl;

      // todo should look for the next packet's payload in the warehouse , in tail recursive call
      return 0;
    }else{ 
      //todo save the partial msg
      return 'p';
    }
  }    
}
void Parser::onUDPPacket(const char *buf, size_t len) {
  size_t const len2 = len;
  //dumpBuffer(buf, len, "into onUDP");
  auto hdr = cast<PacketHeader>(const_cast<char*>(buf));
  //dumpBuffer(buf, len, "after reinterpret_cast, showing in-place endianness conversion");
  cout<<"Received pakt of len = "<<len<<", header showing sz = "<<hdr->sz<<", seq = "<<hdr->seq<<endl;
  if (len != hdr->sz){
      cerr<<"Size value in header differs from buffer length... corrupted buffer, to be discarded."<<endl; return; //no updateSeq()
  }
  size_t const PKT_HDR_SZ = sizeof(PacketHeader);
  if (len < PKT_HDR_SZ){
      cerr<<"buffer too short ... corrupted buffer, to be discarded."<<endl; return; //no updateSeq()
  }
  if (hdr->seq < this->expectedSeq){
    cout<<"Header seq above is a dupe .. dropped"<<endl; return; //no updateSeq()
  }

  if (hdr->seq > this->expectedSeq){ // todo: warehouse it
    return; //no updateSeq()
  }
  assert (hdr->seq == this->expectedSeq );
  cout<<"Header seq above is The Expected .. now processing packet"<<endl;
  if (len == PKT_HDR_SZ ){ cout<<"dummy packet .. taken as a heartbeat"<<endl; 
  }else{
    assert(len > PKT_HDR_SZ ); 
    readPayload(const_cast<char*>(buf)+PKT_HDR_SZ,  len-PKT_HDR_SZ);
  }
  updateSeq(hdr->seq); return;
}
