#pragma once
#include "OrderMsg.h"
#include "PacketHeader.h"
#include <iostream>

//This non-production class is only used for generating test packets
class PacketBuilder{
  char buf[65536] ; //big enough for a UDP packet. no need to initialize
  short offset= sizeof(PacketHeader);
  short lastSeq; // to be overwritten by pack_n_send

public:
  PacketBuilder(short seq=0): lastSeq(seq){}

  template<class T,   typename... Args> //use variadic template args as a hack
  PacketBuilder& fakeMsg(Args... args){
    char* ret = T::fakeMsg(args...);
    size_t sz = sizeof(T);
    memcpy(buf + offset, ret, sz);
    //dumpBuffer(buf + offset, sz, "packet builder's buffer");
    offset += sz;
    return const_cast<PacketBuilder&>(*this); // for chaining
  }

  short pack_n_send (Parser * parser, short seq=0){
    if (seq<=0) seq = lastSeq + 1;
    std::cout<<"sending a fake packet with seq = "<<seq<<" ..\n";
    char* hdr = PacketHeader::fakeMsg(this->offset,seq);
    memcpy(buf, hdr, sizeof(PacketHeader));
    parser->onUDPPacket(this->buf, this->offset);
    return this->lastSeq = seq;
  }
};
