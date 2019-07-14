#pragma once

//#include "Order.h" //circular dependency
//#include "MsgParser.h"
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <cassert>

class Order;
class MsgParser;

class Parser {
    static std::map<char, MsgParser*> workers; //individual msg parsers

    static std::map<std::string, std::map<std::string, int64_t>> actionRecorder; //for simple testing... 1st lookup key is some action id; 2nd key is stock ticker or zero-length string.


    // sequence management:
    uint32_t lastSeq=0, expectedSeq=1; //We only need one of these two fields, but I keep both for convenience.
    void updateSeq(uint32_t processed=0){
      if (processed > 0) assert( lastSeq+1 == expectedSeq && expectedSeq == processed );
      ++lastSeq;
      expectedSeq = lastSeq  + 1;
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

    static //static member func is easiest to use
    char readPayload( char *buf, size_t len) ;

    typedef uint32_t oid_t;
    static std::unordered_map<oid_t, Order> orders;

    static std::ofstream file; //accessible from main() and msg parsers...

    template<class E> 
    static void w2f(E const* ev); //write to file
    static char check (std::string actionId, int64_t exp, std::string stock ="");
    static char record(std::string actionId, int64_t val, std::string stock ="");
};
