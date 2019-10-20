/* 
Not fully tested

showcase: uint8_t is unprintable, so to print a low char value I cast it to uint32_t 
showcase static assert
*/
#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <assert.h>
#define ss if(2>1) cout
using namespace std;

template<typename T, size_t idx>
char getByteByPosition(T haystack){
//  cout<<haystack << " = haystack\n";
  static_assert( idx < sizeof(T) );
  char*ptr  = reinterpret_cast<char*>((&haystack));
  char ret  = ptr[idx];
  cout<<"ret = "<<(uint32_t)ret<<endl;
  return ret;
}
int main(){
  auto ret0 = getByteByPosition<int, 0>(256+31); assert(31==ret0 );
  auto ret1 = getByteByPosition<int, 1>(256+31); assert( 1==ret1 );
}/*MLP coding question on Ashish
Note: byte #1 in an integer is the 2nd lowest byte
*/