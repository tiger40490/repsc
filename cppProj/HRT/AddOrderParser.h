#pragma once
#include "Parser.h"
#include "Order.h"
#include "BaseEvent.h"
#include "utils.h"
#include "MsgParser.h"

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
      ss1<<"qty = "<<qty<<" , stock = "<<stock_()<<",pxFloat = "<<pxFloat<< ", nanosEp = "<<nanosEp<<std::endl;
      return this;
    }
  } __attribute__((packed));
public:
  AddOrderParser(): MsgParser(sizeof(AddOrderMsg)){
    static_assert(sizeof(AddEvent) == 44);
  }
  char parse(char *buf) override{
    auto * msg = cast<AddOrderMsg>(buf);
    Parser::orders.emplace(std::make_pair(msg->oid, msg));
    ss2<<"Order ID's currently saved in order lookup table : ";
    for(auto it = Parser::orders.begin(); it != Parser::orders.end(); ++it){ ss2<<it->first<<" "; }
    ss2<<".. Total "<<Parser::orders.size()<<" orders currently in the lookup table.. now recording actions and broadcasting event..\n";
    Parser::record("px#" + std::to_string(msg->oid), msg->px4,  msg->stock_());
    Parser::record("nano#" + std::to_string(msg->oid), msg->nanos%10000000000,  msg->stock_());
    Parser::record("side#" + std::to_string(msg->oid), msg->side, msg->stock_());
    char const* s=msg->stock;
    AddEvent * ev=AddEvent{0x01, sizeof(AddEvent), {s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]}, msg->nanos, msg->oid, msg->side, {'\0','\0','\0'}, msg->qty, (double)msg->px4}.init();
    Parser::w2f(ev);
    return 0; //0 means good
  }
};
