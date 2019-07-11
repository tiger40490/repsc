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

    cout<<"\nsending cxl..\n";
    myParser.readPayload(DecOrderMsg::fakeMsg(1,5,404904049), sizeof(DecOrderMsg));
    assert(0== Parser::check("qDec#1", 95,      "SPY     "));
    cout<<"\nsending cxl with oversized qty..\n";
    myParser.readPayload(DecOrderMsg::fakeMsg(1,5555,404904049), sizeof(DecOrderMsg));
    assert(0== Parser::check("qDecOver#1", 0,   "SPY     "));
    cout<<"\nsending replace..\n";
    myParser.readPayload(RepOrderMsg::fakeMsg(1,3,250,404904049, 200.11*10000), sizeof(RepOrderMsg));
    assert(0== Parser::check("q#3", 250,      "SPY     "));
    assert(0== Parser::check("px#3", 2001100, "SPY     "));
    return 0;
}
int main(int argc, char **argv) {
  test2();
}
