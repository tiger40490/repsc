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

struct AbstractMsg{}; // not in use now

struct MsgParser{
  size_t const msgSz; // should be a private field with a getter
  virtual char parse(char *buf) = 0; //no buffer len needed .. guaranteed to be sufficient
protected:
  MsgParser(size_t sz): msgSz(sz){}
};
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
       return this;
    }
  } __attribute__((packed));
public:
  AddOrderParser(): MsgParser(34){}
  char parse(char *buf) override{
    cout<<"inside AddOrderParser::parse"<<endl;
    //cast
    auto * msg = cast<AddOrderMsg>(buf);
    return 0; //0 means good
  }
};
static map<char, MsgParser*> workers; //todo: could be a static field of Parser

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
    MsgParser * worker = workers[msgType];
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
  dumpBuffer(buf, len, "into onUDP");
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
