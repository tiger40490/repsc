#include <iostream>
#define ss if( 1>0 )cout
using namespace std;

string formatPtr(void* p){
  static size_t const targetLen=3;
  char buf[16]; ss<<buf<<" is the rubbish before memset\n";
  size_t written = sprintf(buf, "%p\0", p);
  ss<<buf<<" ";
  return string(buf).substr( written - targetLen );
}

int main(){
  cout<<formatPtr(new int(1));
}