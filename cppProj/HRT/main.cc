#include "Parser.h"

#include <cstdio>

#include <cstdint>

#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>

const char *inputFile = "test.in";

void checkRecorder(){
  assert(0== Parser::check("px#1", 2000000));
  assert(0== Parser::check("nano#2", 1562544002123456789));
}

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
    checkRecorder();
    return 0;
}
int main(int argc, char **argv) {
  test2();
}
