#pragma once
#include "utils.h" // betoh()

struct PacketHeader{
  uint16_t sz;
  uint32_t seq;

  PacketHeader const * init() {
     sz  = betoh(sz);
     seq = betoh(seq);
     return this;
  }

  static char* fakeMsg(uint16_t h_pktSz, uint32_t h_seq){ //h_ means in host endianness
    static PacketHeader msg; //overwritten again and again
    msg.sz = htobe(h_pktSz);
    msg.seq = htobe(h_seq);
    char* ret = reinterpret_cast<char*>(&msg);
    //static size_t const sz=sizeof(PacketHeader); dumpBuffer(ret, sz, "serialized fake Packet Header");
    return ret;
  }

} __attribute__((packed));
