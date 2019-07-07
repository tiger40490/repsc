#pragma once
#include <cstdio>
#include <chrono> //will be needed
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
    if (sizeof(T) == 4) return be32toh(input); //same as ntohl()
    if (sizeof(T) == 8) return be64toh(input);
    if (sizeof(T) == 2) return be16toh(input);
    assert (false && "programmer error .. unsupported input data type");
    return 0;
}

///// should be defined in utils.c
uint64_t sinceEpoch(uint64_t sinceMidnight){
    using days = std::chrono::duration<int, std::ratio<86400>>;

    std::chrono::nanoseconds lastMidnight =
        std::chrono::time_point_cast<days>(std::chrono::system_clock::now()).time_since_epoch();
    //std::cout<<lastMidnight.count()<<" = lastMidnight in nanos\n"; //verified
    auto ret = lastMidnight.count() + sinceMidnight;
    //std::cout<<"sinceEpoch() returning "<< ret<<" nanos\n";
    return ret;
}
//static 
void dumpBuffer(char const * buf, size_t const len, std::string const headline=""){
  if ( headline.size()) std::cout<<"---- "<<headline<<" ----\n";

  for(size_t i = 0; i< len; ++i){
    printf("%02hhx ", buf[i]);
    if (i%8 == 7) printf("   ");
  }
  printf ("\n");
}
