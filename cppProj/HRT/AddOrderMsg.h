#pragma once
#include "utils.h" // sinceEpoch
//#include <string>

  struct AddOrderMsg{
    char const msgType; //not in use
    uint64_t nanos; //nanos since midnight
    uint64_t oid;
    char const side;
    uint32_t qty;
    char const stock[8];
    uint32_t px4; //price scaled up by 10 four times
    AddOrderMsg const * cleanup(){ // override{
       oid = betoh(oid); qty = betoh(qty); px4 = betoh(px4); nanos = sinceEpoch(betoh(nanos));
       std::cout<<oid<<" = oid, "<<qty<<" = qty, px (scaled up by 10000) = "<<px4<<", nanos since epoch = "<<nanos<<std::endl;
       std::cout<<side<<" = side, stock = "<<std::string(stock, stock+8)<<std::endl;
       assert ((side == 'S' || 'B' == side)  && "Likely programmer error while parsing the SIDE field, as exchange would not send anything beside B or S" );
       return this;
    }
  } __attribute__((packed));
