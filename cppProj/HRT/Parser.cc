#include "Parser.h"

#include <cassert>
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
template<class T> T const * cast(char const* buf) {
    T const * ret = reinterpret_cast<T const*>(buf)->cleanup();
    return ret;
}
void Parser::onUDPPacket(const char *buf, size_t len) {
    auto * hdr = cast<PacketHeader>(buf);
    cout<<"Received pkt of len = "<<len<<", header showing sz = "<<hdr->sz<<", seq = "<<hdr->seq<<endl;
    assert (len == hdr->sz);
}

