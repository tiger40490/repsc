#pragma once
#include "Parser.h"
#include "OrderMsg.h"
#include "Order.h"
#include "BaseEvent.h"
#include "utils.h"
#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <cstddef> //size_t
#include <cassert>

//struct Parser; //#include "Parser.h" //circular dependency ... must use forward declaration

struct MsgParser{ //StatelessMsgParser
  size_t const msgSz; 
  virtual char parse(char *buf) = 0; //no buffer len needed .. guaranteed to be sufficient
protected:
  MsgParser(size_t sz): msgSz(sz){}
};
// move to MsgParser.h, but for vi-IDE, this way is much quicker
class ExeOrderParser: public MsgParser{
struct ExeEvent: public BaseEvent{
  uint32_t qty;
  double pxFloat;
  ExeEvent * init(){
    this->BaseEvent::init();
    qty     = htole(qty);
    pxFloat = htole(pxFloat/(double)10000);
    //dumpBuffer(reinterpret_cast<char*>(this), sizeof(*this), "at end of init");
    std::cout<<"stock = "<<stock_()<<",pxFloat = "<<pxFloat<< ", nanosEp = "<<nanosEp<<std::endl;
    return this;
  }
} __attribute__((packed));
public:
  ExeOrderParser(): MsgParser(sizeof(ExeOrderParser)){}
  char parse(char *buf) override{
//    std::cout<<"inside ExeOrderParser::parse"<<std::endl;
    auto * msg = cast<ExeOrderMsg>(buf);
    //msg->ser4test();

    std::cout<<"Looking up the orders table using order id = "<<msg->oid<<" ..\n";
    if (Parser::orders.count(msg->oid) == 0){
      std::cout<<"order not found. ExecOrder message dropped\n";
      return 'm'; //missing
    }

    Order& order = Parser::orders[msg->oid];
    if (order.qty < msg->qty){
      std::cout<<"Current order qty "<<order.qty<<" is less than execution qty "<<msg->qty<<" ! Will zero out order qty.\n";
      order.qty = 0;
      Parser::record("qExeOver#" + std::to_string(msg->oid), order.qty, order.stock);
    }else{
      order.qty -= msg->qty;
      std::cout<<"order qty reduced to "<<order.qty<<std::endl;
      Parser::record("qExe#" + std::to_string(msg->oid), order.qty, order.stock);
    }
    std::cout<<order<<" is the updated order.. Now sending event..\n";
    auto s=order.stock.c_str();
    ExeEvent * ev=ExeEvent{0x02, sizeof(ExeEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, msg->qty, (double)order.px4}.init();
    Parser::w2f(ev);
    return 0; //0 means good
  }
};
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
  DecOrderParser(): MsgParser(sizeof(DecOrderMsg)){}
  char parse(char *buf) override{
//    std::cout<<"inside DecOrderParser::parse"<<std::endl;
    auto * msg = cast<DecOrderMsg>(buf);
    //msg->ser4test();

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
    std::cout<<order<<" is the updated order.. now sending event\n";
    auto s=order.stock.c_str();
    DecEvent * ev=DecEvent{0x03, sizeof(DecEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, order.qty}.init();
    Parser::w2f(ev);

    Parser::record("qDecEv#" + std::to_string(msg->oid*10000+msg->qty), ev->qty, order.stock);
    return 0; //0 means good
  }
};
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
    std::cout<<"oidNew = "<<oidNew<<" , stock = "<<stock_()<<",pxFloat = "<<pxFloat<< ", nanosEp = "<<nanosEp<<std::endl;
    return this;
  }
} __attribute__((packed));
public:
  RepOrderParser(): MsgParser(sizeof(RepOrderMsg)){}
  char parse(char *buf) override{
//    std::cout<<"inside RepOrderParser::parse"<<std::endl;
    auto * msg = cast<RepOrderMsg>(buf);
    //msg->ser4test();

    std::cout<<"Looking up the orders table using order id = "<<msg->oid<<" ..\n";
    if (Parser::orders.count(msg->oid) == 0){
      std::cout<<"order not found. ReplaceOrder message dropped\n";
      Parser::record("miss#" + std::to_string(msg->oid), 0, "lookupMiss" );
      return 'm'; //missing
    }
    Order& order = Parser::orders[msg->oid];
    std::cout<<order<<" is the original order\n";
    Parser::orders.erase(msg->oid);
    order.px4=msg->px4;
    order.qty=msg->qty;
    Parser::orders.emplace(msg->oidNew, order);
    Parser::record("px#" + std::to_string(msg->oidNew), msg->px4, order.stock);
    Parser::record("q#" + std::to_string(msg->oidNew), msg->qty, order.stock);
    std::cout<<Parser::orders[msg->oidNew]<<" is the updated order in the lookup table.. now sending event ..\n";
    auto s=order.stock.c_str();
    RepEvent * ev=RepEvent{0x04, sizeof(RepEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, msg->oidNew, msg->qty, (double)msg->px4}.init();
    Parser::w2f(ev);
//    Parser::record("qRepEv#" + std::to_string(msg->oid*10000+msg->qty), ev->qty, order.stock);
    return 0; //0 means good
  }
};
class AddOrderParser: public MsgParser{
struct AddEvent: public BaseEvent{
  char side;
  char padding[3];
  uint32_t qty;
  double pxFloat;
  AddEvent * init(){
    this->BaseEvent::init();
    qty     = htole(qty);
    pxFloat = htole(pxFloat/(double)10000);
    //dumpBuffer(reinterpret_cast<char*>(this), sizeof(*this), "at end of init");
    std::cout<<"qty = "<<qty<<" , stock = "<<stock_()<<",pxFloat = "<<pxFloat<< ", nanosEp = "<<nanosEp<<std::endl;
    return this;
  }
} __attribute__((packed));
public:
  AddOrderParser(): MsgParser(sizeof(AddOrderMsg)){}
  char parse(char *buf) override{
    //std::cout<<"inside AddOrderParser::parse"<<std::endl;
    auto * msg = cast<AddOrderMsg>(buf);
    //msg->ser4test();

    Parser::orders.emplace(std::make_pair(msg->oid, msg));
    std::cout<<"Order ID's currently saved in order lookup table : ";
    for(auto it = Parser::orders.begin(); it != Parser::orders.end(); ++it){ std::cout<<it->first<<" "; }
    Parser::record("px#" + std::to_string(msg->oid), msg->px4,  msg->stock_());
    Parser::record("nano#" + std::to_string(msg->oid), msg->nanos%10000000000,  msg->stock_());
    Parser::record("side#" + std::to_string(msg->oid), msg->side, msg->stock_());
    std::cout<<Parser::orders.size()<<" orders currently in the lookup table.. now sending event..\n";
    char const* s=msg->stock;
    AddEvent * ev=AddEvent{0x01, sizeof(AddEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, msg->side, {'\0','\0','\0'}, msg->qty, (double)msg->px4}.init();
    Parser::w2f(ev);
    return 0; //0 means good
  }
};
