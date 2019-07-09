#pragma once
#include "utils.h" 

  struct AddOrderMsg: public AbstractMsg{
    char const side;
    uint32_t qty;
    char const stock[8];
    uint32_t px4; //price scaled up by 10, four times
    AddOrderMsg const * cleanup(){
       oid = betoh(oid); qty = betoh(qty); px4 = betoh(px4); nanos = sinceEpoch(betoh(nanos));
       std::cout<<oid<<" = oid, "<<qty<<" = qty, px (scaled up by 10000) = "<<px4<<", nanos since epoch = "<<nanos<<std::endl;
       std::cout<<side<<" = side, stock = "<<std::string(stock, stock+8)<<std::endl;
       assert ((side == 'S' || 'B' == side)  && "Likely programmer error while parsing the SIDE field, as exchange would not send anything beside B or S" );
       return this;
    }

    char* ser4test() const{
       AddOrderMsg clone(*this);
       clone.oid = htobe(this->oid);
       clone.qty = htobe(this->qty);
       clone.px4 = htobe(this->px4);
       clone.nanos = htobe(this->nanos%10000000000);
       auto ret = reinterpret_cast<char*> (&clone);
       dumpBuffer(ret, sizeof(AddOrderMsg), "serialized msg");
       return ret;
    }
  } __attribute__((packed));
