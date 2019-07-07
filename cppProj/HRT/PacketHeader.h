#pragma once
#include <arpa/inet.h>

struct PacketHeader{
  uint16_t sz;
  uint32_t seq;
  PacketHeader const * cleanup() {
     sz = ntohs(sz);
     seq = ntohl(seq);
     return this;
  }
} __attribute__((packed));
