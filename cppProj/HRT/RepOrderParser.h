#pragma once
#include "Parser.h"
#include "Order.h"
#include "BaseEvent.h"
#include "utils.h"
#include "MsgParser.h"

class RepOrderParser: public MsgParser{
  struct RepEvent: public BaseEvent{
    uint64_t oidNew;
    uint32_t qty;
    double pxFloat;
    RepEvent * init(){
      this->BaseEvent::init();
      oidNew  = htole(oidNew);
      qty     = htole(qty);
      pxFloat = htole(pxFloat/(double)10000);
      //dumpBuffer(reinterpret_cast<char*>(this), sizeof(*this), "at end of init");
      ss1<<"oidNew = "<<oidNew<<" , stock = "<<stock_()<<",pxFloat = "<<pxFloat<< ", nanosEp = "<<nanosEp<<std::endl;
      return this;
    }
  } __attribute__((packed));
public:
  RepOrderParser(): MsgParser(sizeof(RepOrderMsg)){
    static_assert(sizeof(RepEvent) == 48);
  }
  char parse(char *buf) override{
    auto * msg = cast<RepOrderMsg>(buf);
    ss1<<"Looking up the orders table using order id = "<<msg->oid<<" ..\n";
    if (Parser::orders.count(msg->oid) == 0){
      ss3<<".. Above order id not found. ReplaceOrder message dropped\n";
      Parser::record("miss#" + std::to_string(msg->oid), -1, "lookupMiss" );
      return 'm'; //missing
    }

    ss2<<"Looking up the orders table using replacement order id = "<<msg->oidNew<<" ..\n";
    if (Parser::orders.count(msg->oidNew)){
      ss3<<".. Above replacement order id is already in use .. ReplaceOrder message dropped\n";
      Parser::record("clash#" + std::to_string(msg->oid), -1, "clash" );
      return 'c'; //clash
    }
    Order& order = Parser::orders[msg->oid];
    ss2<<order<<" is the original order\n";
    Parser::orders.erase(msg->oid);
    order.px4=msg->px4;
    order.qty=msg->qty;
    Parser::orders.emplace(msg->oidNew, order);
    Parser::record("px#" + std::to_string(msg->oidNew), msg->px4, order.stock);
    Parser::record("q#" + std::to_string(msg->oidNew), msg->qty, order.stock);
    ss2<<Parser::orders[msg->oidNew]<<" is the replacement order in the lookup table.. now broadcasting event ..\n";
    auto s=order.stock.c_str();
    RepEvent * ev=RepEvent{0x04, sizeof(RepEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, msg->oidNew, msg->qty, (double)msg->px4}.init();
    Parser::w2f(ev);
    return 0; //0 means good
  }
};
