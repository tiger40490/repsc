#pragma once
#include "OrderMsg.h"
#include "PacketHeader.h"

//This class is only used for generating test packets, not production
class PacketBuilder{
  char buf[65536] ; //big enough for a UDP packet. no need to initialize
  short offset= sizeof(PacketHeader);

public:
  template<class T,   typename... Args>
  char* fakeMsg(Args... args){
    char* ret = T::fakeMsg(args...);
    size_t sz = sizeof(T);
    memcpy(buf + offset, ret, sz);
    dumpBuffer(buf + offset, sz, "builder's buffer");
    offset += sz;
    return ret; //not in use
  }

  char pack_n_send (Parser * parser, short seq){
    char* hdr = PacketHeader::fakeMsg(this->offset,seq);
    memcpy(buf, hdr, sizeof(PacketHeader));
    parser->onUDPPacket(this->buf, this->offset);
  }
};
