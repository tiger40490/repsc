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
  if (len != hdr->sz){
      cerr<<"Size value in header differs from buffer length. Will discard buffer."<<endl;
      return;
  }
  if (hdr->seq < 1 + this->lastSeq){
    cout<<"Header seq above is a dupe .. dropped"<<endl;
    return;
  }
  // need to handle seq num 
  assert (hdr->seq == 1 + this->lastSeq );
  cout<<"Header seq above is The Expected .. now processing packet"<<endl;


  updateSeq(hdr->seq); return;
}

