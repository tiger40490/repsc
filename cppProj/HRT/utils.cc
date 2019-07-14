#include "utils.h"
#include <chrono>
#include <iostream>
#include <iomanip>
using namespace std;

uint64_t sinceEpoch(uint64_t sinceMidnight){
    using namespace std::chrono; //scoped USING .. safe even in headers
    using days = duration<int, std::ratio<86400>>;

    std::chrono::nanoseconds lastMidnight =
        time_point_cast<days>(system_clock::now()).time_since_epoch();

    //std::cout<<lastMidnight.count()<<" = lastMidnight in nanos\n"; //verified
    auto ret = lastMidnight.count() + sinceMidnight;

    //std::cout<<"sinceEpoch() returning "<< ret<<" nanos\n";
    return ret;
}

void dumpBuffer(char const * buf, size_t const len, std::string const headline, uint8_t logLevel4this){
  if (LOG_LEVEL > logLevel4this) return;
  if ( headline.size()) std::cout<<"---- "<<headline<<" ----\n";

  for(size_t i = 0; i< len; ++i){
    printf("%02hhx ", buf[i]);
    if (i%8 == 7) printf("   ");
  }
  printf ("\n");
}
