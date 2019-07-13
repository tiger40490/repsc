#include "utils.h"
#include "Parser.h"
#include "OrderMsg.h"
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

    cout<<"\n ---- sending cxl.. 55 shares\n";
    myParser.readPayload(DecOrderMsg::fakeMsg(1,55,404904049), sizeof(DecOrderMsg));
    assert(0== Parser::check("qDec#1",   45,      "SPY     "));
    assert(0== Parser::check("qDecEv#10055", 45,      "SPY     "));
    cout<<"\nsending cxl with oversized qty..\n";
    myParser.readPayload(DecOrderMsg::fakeMsg(1,5555,404904049), sizeof(DecOrderMsg));
    assert(0== Parser::check("qDecOver#1", 0,   "SPY     "));
    assert(0== Parser::check("qDecEv#15555", 0,   "SPY     "));
    cout<<"\n ---- sending exe.. \n";
    myParser.readPayload(ExeOrderMsg::fakeMsg(2,54,404904049), sizeof(ExeOrderMsg));
    assert(0== Parser::check("qExe#2", 46,      "SPY     "));

    { // to limit variable scope
      cout<<"\n  ----- replace -----\n";
      auto oidNew = 3; auto qty = 101; auto px4=200.11*10000;
      myParser.readPayload( RepOrderMsg::fakeMsg(1,oidNew,qty,404904049, px4 )
                          , sizeof(RepOrderMsg));
      assert(0== Parser::check("q#3",  qty, "SPY     "));
      assert(0== Parser::check("px#3", px4, "SPY     "));

      cout<<"\n sending replace for bad order id..\n";
      auto oidOld = 1; //already replace
      myParser.readPayload(RepOrderMsg::fakeMsg(oidOld,oidNew,qty,404904049, px4 ), sizeof(RepOrderMsg));
      assert(0== Parser::check("miss#1", -1, "lookupMiss" ));
    }

    return 0;
}
int main(int argc, char **argv) {
  test2();
  Parser::file.close();
}
