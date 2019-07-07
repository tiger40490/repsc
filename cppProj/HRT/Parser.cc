#include "Parser.h"

#include <string>
#include <cstdio>
#include <arpa/inet.h>
#include <iostream>
#include <deque>
using namespace std;

Parser::Parser(int date, const std::string &outputFilename) {
}

struct PacketHeader{
  mutable uint16_t sz;
  mutable uint32_t seq;
  PacketHeader const * cleanup() const{
     sz = ntohs(sz);
     seq = ntohs(seq);
     return this;
  }
};
void Parser::onUDPPacket(const char *buf, size_t len) {
    printf("Received packet of size %zu\n", len);
    // optionally validate len
    PacketHeader const * hdr = reinterpret_cast<PacketHeader const*>(buf)->cleanup();
    cout<<"pkg hdr sz = "<<hdr->sz<<" , seq = "<<hdr->seq<<endl;
}

