#pragma once
#include "Parser.h"
#include "Order.h"
#include "BaseEvent.h"
#include "utils.h"
#include "MsgParser.h"

class ExeOrderParser: public MsgParser{
  struct ExeEvent: public BaseEvent{
    uint32_t qty;
    double pxFloat;
    ExeEvent * init(){
      this->BaseEvent::init();
      qty     = htole(qty);
      pxFloat = htole(pxFloat/(double)10000);
      //dumpBuffer(reinterpret_cast<char*>(this), sizeof(*this), "at end of init");
      //std::cout<<"BaseEvent convertion done: stock = "<<stock_()<<",pxFloat = "<<pxFloat<< ", nanosEp = "<<nanosEp<<std::endl;
      return this;
    }
  } __attribute__((packed));

public:
  ExeOrderParser(): MsgParser(sizeof(ExeOrderMsg)){
    static_assert(sizeof(ExeEvent) == 40);
  }
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
    std::cout<<order<<" is the updated order.. Now broadcasting event..\n";
    auto s=order.stock.c_str();
    ExeEvent * ev=ExeEvent{0x02, sizeof(ExeEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, msg->qty, (double)order.px4}.init();
    Parser::w2f(ev);
    return 0; //0 means good
  }
};
