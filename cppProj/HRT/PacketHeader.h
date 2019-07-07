#pragma once
#include <arpa/inet.h>

struct PacketHeader{
  mutable uint16_t sz;
  mutable uint32_t seq;
  PacketHeader const * cleanup() const{
     sz = ntohs(sz);
     seq = ntohl(seq);
     return this;
  }
} __attribute__((packed));
