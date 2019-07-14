#pragma once
#include "Parser.h"
#include "Order.h"
#include "BaseEvent.h"
#include "utils.h"
#include "MsgParser.h"

class DecOrderParser: public MsgParser{
  struct DecEvent: public BaseEvent{
    uint32_t qty;
    DecEvent * init(){
      this->BaseEvent::init();
      qty     = htole(qty);
      //dumpBuffer(reinterpret_cast<char*>(this), sizeof(*this), "at end of init");
      std::cout<<"qty rem = "<<qty<<" , stock = "<<stock_()<<", nanosEp = "<<nanosEp<<std::endl;
      return this;
    }
  } __attribute__((packed));
public:
  DecOrderParser(): MsgParser(sizeof(DecOrderMsg)){
    static_assert(sizeof(DecEvent) == 32);
  }
  char parse(char *buf) override{
//    std::cout<<"inside DecOrderParser::parse"<<std::endl;
    auto * msg = cast<DecOrderMsg>(buf);
    std::cout<<"Looking up the orders table using order id = "<<msg->oid<<" ..\n";
    if (Parser::orders.count(msg->oid) == 0){
      std::cout<<"order not found. CancelOrder message dropped\n";
      return 'm'; //missing
    }
    Order& order = Parser::orders[msg->oid];
    if (order.qty < msg->qty){
      std::cout<<"Current order qty "<<order.qty<<" is less than cancel qty "<<msg->qty<<" ! Will zero out order qty.\n";
      order.qty = 0;
      Parser::record("qDecOver#" + std::to_string(msg->oid), order.qty, order.stock);
    }else{
      order.qty -= msg->qty;
      std::cout<<"order qty reduced to "<<order.qty<<std::endl;
      Parser::record("qDec#" + std::to_string(msg->oid), order.qty, order.stock);
    }
    std::cout<<order<<" is the updated order.. now broadcasting event\n";
    auto s=order.stock.c_str();
    DecEvent * ev=DecEvent{0x03, sizeof(DecEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, order.qty}.init();
    Parser::w2f(ev);
    Parser::record("qDecEv#" + std::to_string(msg->oid*10000+msg->qty), ev->qty, order.stock);
    return 0; //0 means good
  }
};
