#pragma once
#include <cstddef> 

struct BaseEvent{
  uint16_t evType;
  uint16_t evSz;
  char const stock[8];
  uint64_t nanosEp; //since Epoch
  uint64_t oid;

  inline std::string stock_() const {return std::string(stock, stock+8); }

  void init(){
    evType  = htole(evType);
    evSz    = htole(evSz);
    nanosEp = htole(nanosEp);
    oid     = htole(oid);
  }
} __attribute__((packed));

