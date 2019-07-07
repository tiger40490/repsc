#pragma once

#include <string>
#include <cassert>

class Parser {
  uint32_t lastSeq=0, nextSeq=1; //We only need one of these two fields, but I keep both for convenience.
  void updateSeq(uint32_t processed){
    assert( lastSeq+1 == nextSeq && nextSeq == processed );
    ++lastSeq;
    nextSeq = lastSeq  + 1;
  }
  public:
    // date - the day on which the data being parsed was generated.
    // It is specified as an integer in the form yyyymmdd.
    // For instance, 18 Jun 2018 would be specified as 20180618.
    //
    // outputFilename - name of the file output events should be written to.
    Parser(int date, const std::string &outputFilename);

    // buf - points to a char buffer containing bytes from a single UDP packet.
    // len - length of the packet.
    void onUDPPacket(const char *buf, size_t len);
};
