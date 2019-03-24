//showcase jump-increment within member initliazation expression
//showcase throwing and catching string
#include <iostream>
using namespace std;

struct C{
  static int cnt;
  int const _i;
  C(): _i(cnt+=2){
    if (_i>8) throw string("bad value in data member this->_i = ") + to_string(this->_i);
    cout<<_i<<" constructed\n";
  }
  ~C(){cout<<_i<<" destructed in reverse sequence\n"; }
};
int C::cnt=0;
int main(){
  try{
    C* arr = new C[99];
  }catch(string & err){
    cout<<err;
  }
}