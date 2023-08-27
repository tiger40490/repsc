#include <iostream>
#include <memory> //unique_ptr
#include <assert.h>
using namespace std;

void test(size_t cnt){
    size_t bytes{ sizeof(string) * cnt };
    cerr<<bytes<<" bytes to be allocated via malloc\n";
    void * rawPtr{ malloc(bytes) };
    cerr<<bytes<<" bytes allocated via malloc\n";
}

int main(){
  for (size_t i = 1; i< 17; i*=2){
    test(i);
  }
}