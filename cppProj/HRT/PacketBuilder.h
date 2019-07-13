#pragma once
#include "OrderMsg.h"

//This class is only used for generating test packets, not production
class PacketBuilder{
  char buf[65536] ; //big enough for a UDP packet. no need to initialize
  short offset=6; //for the packet header
public:
  template<class T,   typename... Args>
  char* fakeMsg(Args... args){
    char* ret = T::fakeMsg(args...);
    size_t sz = sizeof(T);
    
    memcpy(buf + offset, ret, sz);
    dumpBuffer(buf + offset, sz, "builder's buffer");
    offset += sz;
  }
};
