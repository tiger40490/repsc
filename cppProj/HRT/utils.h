#pragma once
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cassert>

//should move to MsgParser.h:
struct AbstractMsg{ 
    char const msgType; //not in use
  //virtual ~AbstractMsg(){} //breaks reinterpret_cast
};

template<class T> 
T const*  cast(char* buf) { // buf content is modified .. not const char*
    T const * ret = reinterpret_cast<T*>(buf)->cleanup();
    return ret;
}

template <typename T> T htobe(const T &input) { // only for testing
    constexpr size_t s = sizeof(T);
    static_assert( (s==2||s==4||s==8) && "programmer error .. unsupported input data type");

    if (s == 4) return htobe32(input); 
    if (s == 8) return htobe64(input);
    if (s == 2) return htobe16(input);
    throw "Unsupported input data type";
}
template <typename T> T htole(const T &input) { // for output to file
    constexpr size_t s = sizeof(T);
    static_assert( (s==2||s==4||s==8) && "programmer error .. unsupported input data type");

    if (s == 4) return htole32(input); 
    if (s == 8) return htole64(input);
    if (s == 2) return htole16(input);
    throw "Unsupported input data type";
}
template <typename T> T betoh(const T &input) {
    constexpr size_t s = sizeof(T);
    static_assert( (s==2||s==4||s==8) && "programmer error .. unsupported input data type");

    if (s == 4) return be32toh(input); //same as ntohl()
    if (s == 8) return be64toh(input);
    if (s == 2) return be16toh(input);
    throw "Unsupported input data type";
}

//static  // static or inline required if in header
void dumpBuffer(char const * buf, size_t const len, std::string const headline="");
uint64_t sinceEpoch(uint64_t sinceMidnight);
