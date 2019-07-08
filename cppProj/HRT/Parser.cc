/* todo: Parser ctor 
*/
#include "Parser.h"
#include "PacketHeader.h"
#include "utils.h"

#include <cassert>
#include <iostream>
#include <deque>
#include <map>
using namespace std;

// move to AddOrderParser.h or MsgParser.h
class AddOrderParser: public MsgParser{
  struct AddOrderMsg: public AbstractMsg{
    char const msgType; //not in use
    uint64_t nanos; //nanos since midnight
    uint64_t oid;
    char const side;
    uint32_t qty;
    char const stock[8];
    uint32_t px4; //price scaled up by 10 four times
    AddOrderMsg const * cleanup(){ // override{
       oid = betoh(oid); qty = betoh(qty); px4 = betoh(px4); nanos = sinceEpoch(betoh(nanos));
       cout<<oid<<" = oid, "<<qty<<" = qty, px (scaled up by 10000) = "<<px4<<", nanos since epoch = "<<nanos<<endl;
       cout<<side<<" = side, stock = "<<string(stock, stock+8)<<endl;
       assert ((side == 'S' || 'B' == side)  && "Likely programmer error while parsing the SIDE field, as exchange would not send anything beside B or S" );
       return this;
    }
  } __attribute__((packed));
public:
  AddOrderParser(): MsgParser(34){}
  char parse(char *buf) override{
    //cout<<"inside AddOrderParser::parse"<<endl;
    auto * msg = cast<AddOrderMsg>(buf);
    Parser::record("px#" + to_string(msg->oid), msg->px4);
    Parser::record("nano#" + to_string(msg->oid), msg->nanos);
    return 0; //0 means good
  }
};
///////////
map<char, MsgParser*> Parser::workers;
std::unordered_map<uint32_t, Order> Parser::orders;
map<std::string, map<std::string, uint64_t>> Parser::eventRecorder;
char Parser::record(std::string eventId, uint64_t val, std::string stock ){
  if (Parser::eventRecorder.count(eventId) ){
     assert(Parser::eventRecorder[eventId].count(stock) ==0 && "Programmer error.. repeated eventId for the same stock" );
     return 'r';  //repeat
  }
  Parser::eventRecorder[eventId][stock] = val;
  cout<<val<<" recorded against "<<eventId<<endl;
  return 0; 
}
char Parser::check(std::string eventId, uint64_t exp, std::string stock){
  if (Parser::eventRecorder.count(eventId) == 0) return 'e'  ; //event id not in recorder
  if (Parser::eventRecorder[eventId].count(stock) == 0) return 's';
  if (Parser::eventRecorder[eventId][stock] != exp ) return 'u' ;  //unequal
  cout<<exp<<" verified against "<<eventId<<endl;
  return 0;
}

Parser::Parser(int date, const std::string &outputFilename) {
  if (workers.empty()){
    workers['A'] = new AddOrderParser();
//  workers['E'] = new ExeOrder();
//  workers['X'] = new CxlOrder();
//  workers['R'] = new RepOrder();
  }
}
char readBody( char *buf, size_t len) {
  cout<<len<<" = len in readBody()"<<endl;
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
      cout<<cnt<<" messages parsed and packet is exhausted"<<endl;
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
  if (hdr->seq < 1 + this->lastSeq){
    cout<<"Header seq above is a dupe .. dropped"<<endl; return; //no updateSeq()
  }
  // need to handle seq num 
  assert (hdr->seq == 1 + this->lastSeq );
  cout<<"Header seq above is The Expected .. now processing packet"<<endl;
  if (len == PKT_HDR_SZ ){ cout<<"dummy packet .. taken as a heartbeat"<<endl; 
  }else{
    assert(len > PKT_HDR_SZ ); 
    readBody(const_cast<char*>(buf)+PKT_HDR_SZ,  len-PKT_HDR_SZ);
  }
  updateSeq(hdr->seq); return;
}
