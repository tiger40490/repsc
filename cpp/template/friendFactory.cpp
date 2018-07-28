//todo: singleton
#include <iostream>
using namespace std;

template<typename T> T* create(){
  return new T();
}
class C{
  C() {cout<<"C ctor, private\n";}
public:  
  ~C(){cout<<"C dtor, must be public to support delete\n";}
  friend C* create<C>();
};
class C2{
  C2() {cout<<"C2 ctor, private\n";}
  friend C2* create<C2>();
};
int main(){
  auto ptr //asterisk is optional but better IMO 
    = create<C>();
  delete ptr;
  auto * ptr2 = create<C2>();
}