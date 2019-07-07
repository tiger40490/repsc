#pragma once
#include "utils.h" // betoh()

struct PacketHeader{
  uint16_t sz;
  uint32_t seq;
  PacketHeader const * cleanup() {
     sz  = betoh(sz);
     seq = betoh(seq);
     return this;
  }
} __attribute__((packed));
