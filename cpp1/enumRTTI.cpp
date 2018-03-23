#include <iostream>
#include <stdint.h> //uint8_t
using namespace std;

enum Type: uint8_t {b, d1, d2};
struct MyBase{
  Type type;
  MyBase():type(b){ cout<<"MyBase ctor\n";}
};
struct MyDer1: public MyBase{
  MyDer1(){ cout<<"MyDer1 ctor\n"; type = d1;}
};
void identify(MyBase * ptr){
  cout<<"v v v   entering identify()...\n";
  switch (ptr->type){
    case b:
        cout<<"MyBase object of size ";
        break;
    case d1:
        cout<<"MyDer1 object of size ";
  }
  cout<<sizeof(*ptr)<<", which is much smaller than a vptr:)\n^ ^ ^   leaving identify()\n\n";
}
struct RegularVptrBased{
  virtual ~RegularVptrBased(){}
};
int main(){
  identify(new MyDer1);
  identify(new MyBase);
  cout<<sizeof(RegularVptrBased)<<" = size of a vptr-based class\n";
}
