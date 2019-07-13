#include "Parser.h"
#include "Order.h"
#include "PacketHeader.h"
#include "OrderMsg.h"
#include "utils.h"

#include <cassert>
#include <iostream>
#include <deque>
#include <map>
using namespace std;
//move to Event.h
struct BaseEvent{
  uint16_t evType;
  uint16_t evSz;
  char stock[8];
  uint64_t nanosEp;
  uint64_t oid;
  inline std::string stock_() const {return std::string(stock, stock+8); }
  void init(){
    evType = htole(evType);
    evSz = htole(evSz);
    nanosEp = htole(nanosEp);
    oid = htole(oid);
//    cout<<"BaseEvent::init() done\n";
  }
} __attribute__((packed));
struct ExeEvent: public BaseEvent{
  uint32_t qty;
  double pxFloat;
  ExeEvent * init(){
    this->BaseEvent::init();
    qty     = htole(qty);
    pxFloat = htole(pxFloat/(double)10000);
    dumpBuffer(reinterpret_cast<char*>(this), sizeof(*this), "at end of init");
    cout<<"stock = "<<stock_()<<",pxFloat = "<<pxFloat<< ", nanosEp = "<<nanosEp<<endl;
    return this;
  }
} __attribute__((packed));

// move to MsgParser.h, but for vi-IDE, this way is much quicker
class ExeOrderParser: public MsgParser{
public:
  ExeOrderParser(): MsgParser(sizeof(ExeOrderParser)){}
  char parse(char *buf) override{
    cout<<"inside ExeOrderParser::parse"<<endl;
    auto * msg = cast<ExeOrderMsg>(buf);
    msg->ser4test();

    cout<<"Looking up the orders table using order id = "<<msg->oid<<" ..\n";
    if (Parser::orders.count(msg->oid) == 0){
      cout<<"order not found. ExecOrder message dropped\n";
      return 'm'; //missing
    }

    Order& order = Parser::orders[msg->oid];
    if (order.qty < msg->qty){
      cout<<"Current order qty "<<order.qty<<" is less than execution qty "<<msg->qty<<" ! Will zero out order qty.\n";
      order.qty = 0;
      Parser::record("qExeOver#" + to_string(msg->oid), order.qty, order.stock);
    }else{
      order.qty -= msg->qty;
      cout<<"order qty reduced to "<<order.qty<<endl;
      Parser::record("qExe#" + to_string(msg->oid), order.qty, order.stock);
    }
    cout<<order<<" is the updated order.. Now sending event..\n";
    auto s=order.stock.c_str();
    ExeEvent * ev=ExeEvent{0x02, sizeof(ExeEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, msg->qty, (double)order.px4}.init();

    //static char serBuf[sz]; //to be overwritten each time

    Parser::w2f(ev);
    return 0; //0 means good
  }
};
class DecOrderParser: public MsgParser{
public:
  DecOrderParser(): MsgParser(sizeof(DecOrderMsg)){}
  char parse(char *buf) override{
    cout<<"inside DecOrderParser::parse"<<endl;
    auto * msg = cast<DecOrderMsg>(buf);
    msg->ser4test();

    cout<<"Looking up the orders table using order id = "<<msg->oid<<" ..\n";
    if (Parser::orders.count(msg->oid) == 0){
      cout<<"order not found. CancelOrder message dropped\n";
      return 'm'; //missing
    }

    Order& order = Parser::orders[msg->oid];
    if (order.qty < msg->qty){
      cout<<"Current order qty "<<order.qty<<" is less than cancel qty "<<msg->qty<<" ! Will zero out order qty.\n";
      order.qty = 0;
      Parser::record("qDecOver#" + to_string(msg->oid), order.qty, order.stock);
    }else{
      order.qty -= msg->qty;
      cout<<"order qty reduced to "<<order.qty<<endl;
      Parser::record("qDec#" + to_string(msg->oid), order.qty, order.stock);
    }
    cout<<order<<" is the updated order\n";

    // now send msg out
    return 0; //0 means good
  }
};
class RepOrderParser: public MsgParser{
public:
  RepOrderParser(): MsgParser(sizeof(RepOrderMsg)){}
  char parse(char *buf) override{
    cout<<"inside RepOrderParser::parse"<<endl;
    auto * msg = cast<RepOrderMsg>(buf);
    msg->ser4test();

    cout<<"Looking up the orders table using order id = "<<msg->oid<<" ..\n";
    if (Parser::orders.count(msg->oid) == 0){
      cout<<"order not found. ReplaceOrder message dropped\n";
      Parser::record("miss#" + to_string(msg->oid), 0, "lookupMiss" );
      return 'm'; //missing
    }

    Order& order = Parser::orders[msg->oid];
    cout<<order<<" is the original order\n";
    Parser::orders.erase(msg->oid);
    order.px4=msg->px4;
    order.qty=msg->qty;
    Parser::orders.emplace(msg->oidNew, order);
    cout<<Parser::orders[msg->oidNew]<<" is the updated order in the lookup table\n";

    Parser::record("px#" + to_string(msg->oidNew), msg->px4, order.stock);
    Parser::record("q#" + to_string(msg->oidNew), msg->qty, order.stock);
    return 0; //0 means good
  }
};
class AddOrderParser: public MsgParser{
public:
  AddOrderParser(): MsgParser(sizeof(AddOrderMsg)){}
  char parse(char *buf) override{
    //cout<<"inside AddOrderParser::parse"<<endl;
    auto * msg = cast<AddOrderMsg>(buf);

    msg->ser4test();

    Parser::orders.emplace(make_pair(msg->oid, msg));
    cout<<"Order ID's currently saved in order lookup table : ";
    for(auto it = Parser::orders.begin(); it != Parser::orders.end(); ++it){ cout<<it->first<<" "; }
    std::cout<<Parser::orders.size()<<" orders currently in the lookup table\n";
    Parser::record("px#" + to_string(msg->oid), msg->px4,  msg->stock_());
    Parser::record("nano#" + to_string(msg->oid), msg->nanos%10000000000,  msg->stock_());
    Parser::record("side#" + to_string(msg->oid), msg->side, msg->stock_());
    return 0; //0 means good
  }
};
/////////// now the static fields and other members of Parser class
ofstream Parser::file;
std::map<char, MsgParser*> Parser::workers;
std::unordered_map<uint32_t, Order> Parser::orders;
std::map<std::string, map<std::string, uint64_t>> Parser::eventRecorder;

template<class E> void Parser::w2f(E const* ev){
    file.write(reinterpret_cast<char const*>(ev), sizeof(E));
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
