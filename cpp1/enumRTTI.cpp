//note ctor runs before the function receives the new ptr

#include <iostream>
#include <stdint.h> //uint8_t
using namespace std;

struct MyBase{
  enum Type: uint8_t {b, d1, d2};
  Type type;
  //MyBase(): MyBase(b){} //c++11 ctor chaining not supported in my compiler:(
  MyBase(Type t):type(t){ cout<<"MyBase ctor\n";}
};
struct MyDer1: public MyBase{ //note ctor can't initialize the field "type" directly
  MyDer1() : MyBase(MyBase::d1) { cout<<"MyDer1 ctor\n"; }
};
void identify(MyBase * ptr){
  cout<<"v v v   entering identify()...\n";
  switch (ptr->type){
    case MyBase::b:
        cout<<"MyBase object of size == ";
        break;
    case MyBase::d1:
        cout<<"MyDer1 object of size == ";
  }
  cout<<sizeof(*ptr)<<", which is much smaller than a vptr:)\n^ ^ ^   leaving identify()\n\n";
}
struct RegularVptrBased{
  virtual ~RegularVptrBased(){}
};
int main(){
  identify(new MyDer1);
  identify(new MyBase(MyBase::b));
  cout<<sizeof(RegularVptrBased)<<" = size of a vptr-based class\n";
}
/*demonstrates use of one-byte enum field instead of 8-byte vptr for RTTI
 */
