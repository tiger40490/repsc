//demo: ctor runs before the function receives the new ptr
//demo: the enum is a nested type within a struct, so enum value like
// "b" is MyBase::b. In c++11, we would use the enum class as qualifier
//showcase c++11 ctor chaining 
#include <iostream>
#include <stdint.h> //uint8_t
using namespace std;

struct MyBase{
  enum Level: uint8_t {b, d1, d2};
  Level type;
  MyBase(): MyBase(b){} //c++11 ctor chaining not supported in my office compiler:(
  void play(){ cout<<"MyBase playing\n"; }
protected:
  MyBase(Level t):type(t){ cout<<"MyBase ctor\n";}
};
struct MyDer1: public MyBase{ //note ctor can't initialize the field "type" directly
  MyDer1() : MyBase(MyBase::d1) { cout<<"MyDer1 ctor\n"; }
  void play(){ cout<<"MyDer1 playing()\n"; }
};
void identifyType(MyBase * ptr){
  cout<<"v v v   entering identify()...\nCalling non-virtual function via base ptr: ";
  ptr->play();
  switch (ptr->type){
    case MyBase::b:
        ptr->play();
        cout<<"MyBase object of size == ";
        break;
    case MyBase::d1:
        MyDer1 * p1 = static_cast<MyDer1*>(ptr);
        p1->play();
        cout<<"MyDer1 object of size == ";
  }
  cout<<sizeof(*ptr)<<", which is much smaller than a vptr:)\n^ ^ ^   leaving identify()\n\n";
}
struct RegularVptrBased{
  virtual ~RegularVptrBased(){}
};
int main(){
  identifyType(new MyDer1);
  identifyType(new MyBase(/*MyBase::b*/));
  cout<<sizeof(RegularVptrBased)<<" = size of a vptr-based class\n";
}
/* Demonstrates use of one-byte enum field instead of 8-byte vptr for RTTI
 * Once we know the runtime type we could static_cast the pointer and invoke non-virtual functions.
 * This is space-efficient if we construct many instances, but not necessarily runtime efficient.
 */
