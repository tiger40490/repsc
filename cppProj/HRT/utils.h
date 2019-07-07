#include <cstdio>
#include <iostream>
#include <iomanip>

template<class T>  // this template has to live in a header file
T const*  cast(char* buf) { // buf content is modified .. not const char*
    T const * ret = reinterpret_cast<T*>(buf)->cleanup();
    return ret;
}

// should be defined in utils.c
//inline 
void dumpBuffer(char const * const buf, size_t const len, std::string headline=""){
  if ( headline.size()) std::cout<<"---- "<<headline<<" ----\n";

  for(size_t i = 0; i< len; ++i){
    printf("%02hhx ", buf[i]);
    if (i%8 == 7) printf("   ");
  }
  printf ("\n");
}
