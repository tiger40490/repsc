/* todo: Parser ctor 
*/
#include "Parser.h"
#include "PacketHeader.h"
#include "utils.h"

#include <cassert>
#include <iostream>
#include <deque>
using namespace std;

Parser::Parser(int date, const std::string &outputFilename) {
  
}
void Parser::onUDPPacket(const char *buf, size_t len) {
    auto hdr = cast<PacketHeader>(buf);
    cout<<"Received pakt of len = "<<len<<", header showing sz = "<<hdr->sz<<", seq = "<<hdr->seq<<endl;
    assert (len == hdr->sz);
}

