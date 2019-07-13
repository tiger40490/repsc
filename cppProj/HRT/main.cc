#include "utils.h"
#include "Parser.h"
#include "OrderMsg.h"
#include "PacketBuilder.h"
#include <cstdio>
#include <cstdint>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <iostream>
using namespace std;

const char *inputFile = "test.in";

int test2(){
    constexpr int currentDate = 20180612;
    Parser myParser(currentDate, "myTestFile");

    int fd = open(inputFile, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Couldn't open %s\n", inputFile);
        return 1;
    }

    char bigbuf[5000];
    while (read(fd, bigbuf, 2) != 0) {
        uint16_t packetSize = htons(*(uint16_t *)bigbuf);
        auto dummy = read(fd, bigbuf + 2, packetSize - 2);

        myParser.onUDPPacket(bigbuf, packetSize);
    }
    close(fd);
    assert(0== Parser::check("px#1", 2000000,      "SPY     "));
    assert(0== Parser::check("o+#1", 100,          "SPY     ")); //o+ means order created in 'orders' container
    assert(0== Parser::check("side#2", 'B',        "SPY     "));
    assert(0== Parser::check("nano#2", 2123456789, "SPY     "));
    // basic basic test done, using the two AddOrder's provided


    { // to limit variable scope
      cout<<"\n  ----- replace -----\n";
      auto oidNew = 3; auto qty = 1000; auto px4=200.11*10000;
      myParser.readPayload( RepOrderMsg::fakeMsg(1,oidNew,qty,404904049040490, px4 )
                          , sizeof(RepOrderMsg));
      assert(0== Parser::check("q#3",  qty, "SPY     "));
      assert(0== Parser::check("px#3", px4, "SPY     "));

      cout<<"\n sending replace for bad order id..\n";
      auto oidOld = 1; //already replace
      myParser.readPayload(RepOrderMsg::fakeMsg(oidOld,oidNew,qty,404904049040490, px4 ), sizeof(RepOrderMsg));
      assert(0== Parser::check("miss#1", -1, "lookupMiss" ));

      cout<<"\n sending replace with bad new order id..\n";
      oidOld = 2; // oidNew is still 3 :(
      myParser.readPayload(RepOrderMsg::fakeMsg(oidOld,oidNew,qty,404904049040490, px4 ), sizeof(RepOrderMsg));
      assert(0== Parser::check("clash#2", -1, "clash" ));

      cout<<"\n ---- exe --- \n";
      auto qtyExe=50; qty -= qtyExe;
      myParser.readPayload(ExeOrderMsg::fakeMsg(3,qtyExe,404904049040490), sizeof(ExeOrderMsg));
      assert(0== Parser::check("qExe#3", qty,      "SPY     "));

      cout<<"\n ---- cxl --- \n";
      auto qtyDec = 55; qty -= qtyDec;
      myParser.readPayload(DecOrderMsg::fakeMsg(3,qtyDec,404904049040490), sizeof(DecOrderMsg));
      assert(0== Parser::check("qDec#3",    qty,      "SPY     "));
      assert(0== Parser::check("qDecEv#30055", qty,"SPY     "));

      cout<<"\nsending cxl with oversized qty..\n";
      myParser.readPayload(DecOrderMsg::fakeMsg(3,5555,404904049040490), sizeof(DecOrderMsg));
      assert(0== Parser::check("qDecOver#3", 0,   "SPY     "));
      assert(0== Parser::check("qDecEv#35555", 0,   "SPY     "));
    }

    return 0;
}
void testPackets(){
  PacketBuilder builder;
  builder.fakeMsg<ExeOrderMsg>(3,555,404904049040490);
}
int main(int argc, char **argv) {
  testPackets();
  return 0;
  test2();
  Parser::file.close();
}

