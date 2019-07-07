/* todo: Parser ctor 
*/
#include "Parser.h"
#include "PacketHeader.h"
#include "utils.h"

#include <cassert>
#include <iostream>
#include <deque>
#include <map>
using namespace std;

struct MsgParser{
  size_t msgSz=34; //fake
  void parse(const char *buf){
    cout<<"inside pppparse"<<endl;
  }
};
map<char, MsgParser*> workers; //should be a nonstatic  field of Parser


Parser::Parser(int date, const std::string &outputFilename) {
  workers['A'] = new MsgParser();
}
char readBody( const char *buf, size_t len) {
  cout<<len<<" = len in readBody()"<<endl;
  dumpBuffer(buf, len);
  for (int cnt=1; ; ++cnt){
      //check msg type then remaining size
    char const msgType = buf[0];
    MsgParser * worker = workers[msgType];
    if (worker == nullptr){
      cerr<<msgType<<" is invalid msgType"<<endl;
      return 'i';
    }
    if (len >= worker->msgSz){
      worker->parse(buf);
      //if (len == worker->msgSz){
      if (len > worker->msgSz){
          len -= worker->msgSz;
          continue;
      }
      assert (len == worker->msgSz);
      cout<<cnt<<" messages parsed and packet is exhausted"<<endl;
      return 0;
    }else{ 
      //todo save the partial msg
      return 'p';
    }
  }    
}
void Parser::onUDPPacket(const char *buf, size_t len) {
  size_t const len2 = len;
  dumpBuffer(buf, len, "into onUDP");
  auto hdr = cast<PacketHeader>(buf);
  //dumpBuffer(buf+6, len-6, "after cast");
  cout<<"Received pakt of len = "<<len<<", header showing sz = "<<hdr->sz<<", seq = "<<hdr->seq<<endl;
  if (len != hdr->sz){
      cerr<<"Size value in header differs from buffer length... corrupted buffer, to be discarded."<<endl; return; //no updateSeq()
  }
  if (len < 6){
      cerr<<"buffer too short ... corrupted buffer, to be discarded."<<endl; return; //no updateSeq()
  }
  if (hdr->seq < 1 + this->lastSeq){
    cout<<"Header seq above is a dupe .. dropped"<<endl; return; //no updateSeq()
  }
  // need to handle seq num 
  assert (hdr->seq == 1 + this->lastSeq );
  cout<<"Header seq above is The Expected .. now processing packet"<<endl;
  size_t const PKT_HDR_SZ=6;
  if (len == PKT_HDR_SZ ){ cout<<"dummy packet .. taken as a heartbeat"<<endl; 
  }else{
    assert(len > PKT_HDR_SZ ); 
    readBody(buf+PKT_HDR_SZ,  len-PKT_HDR_SZ);
  }
  updateSeq(hdr->seq); return;
}

