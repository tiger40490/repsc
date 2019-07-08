#pragma once
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cassert>

template<class T> inline 
T const*  cast(char* buf) { // buf content is modified .. not const char*
    T const * ret = reinterpret_cast<T*>(buf)->cleanup();
    return ret;
}

template <typename T> inline 
T betoh(const T &input) {
    constexpr size_t s = sizeof(T);
    static_assert( (s==2||s==4||s==8) && "programmer error .. unsupported input data type");

    if (s == 4) return be32toh(input); //same as ntohl()
    if (s == 8) return be64toh(input);
    if (s == 2) return be16toh(input);
    return T{9999};
}

//static  // static or inline required if in header
void dumpBuffer(char const * buf, size_t const len, std::string const headline="");

//inline  // static or inline required if in header
uint64_t sinceEpoch(uint64_t sinceMidnight);
