#include <iostream>
using namespace std;

template<typename T> T* create(){
  return (new T());
}
class C{
  C() {cout<<"C ctor, private\n";}
public:  
  ~C(){cout<<"C dtor, must be public to support delete\n";}
  friend C* create<C>();
};

int main(){
  C* ptr = create<C>();
  delete ptr;
}