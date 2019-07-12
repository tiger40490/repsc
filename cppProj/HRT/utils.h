#pragma once
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cassert>

template<class T> 
T const*  cast(char* buf) { // buf content is modified .. not const char*
    T const * ret = reinterpret_cast<T*>(buf)->init();
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
static // static or inline needed to keep this func in header. I prefer to keep this func overload together with the templates. Note func template specialization is a bad idea!
double htole(double d){ //returns the original d value, if on a little-endian CPU
  uint64_t hostFormat;
  static_assert(sizeof hostFormat == sizeof d);
  std::memcpy(&hostFormat, &d, sizeof d); //convert from float to int
  uint64_t const le = htole64(hostFormat); 
  //uint64_t const le = htobe64(hostFormat); //would show a difference in return value 
  double ret;
  std::memcpy(&ret, &le, sizeof d); //convert from int to float
  return ret;
}
template <typename T> T htole(const T &input) { // for output to file
    constexpr size_t s = sizeof(T);
    static_assert( (s==2||s==4||s==8) && "programmer error .. unsupported input data type"); //tested
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
