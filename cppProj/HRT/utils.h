#include <cstdio>
#include <iostream>
#include <iomanip>

template<class T>  // this template has to live in a header file
T const*  cast(char const* buf) {
    T const* ret = reinterpret_cast<T const*>(buf)->cleanup();
    return ret;
}

inline void dumpBuffer(char const * const buf, size_t const len, std::string headline=""){
  if ( headline.size()) std::cout<<"---- "<<headline<<" ----\n";

  for(size_t i = 0; i< len; ++i){
    printf("%02hhx ", buf[i]);
    if (i%8 == 7) printf("   ");
  }
  printf ("\n");
}
