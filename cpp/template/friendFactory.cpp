//showcase: singleton enforced by private ctor and factory (instead of static method)
//showcase: template factory function to support any number of target classes

/*Showcasing two ways to keep cached instances:
1) static local variable in each distinct instantiation of create(). 
2) factory maintains a single instance of each type. The lookup map uses typeid as key, and void pointer as value.
*/
#include <typeindex>
#include <typeinfo>
#include <map>
#include <iostream>
#include <cassert>
using namespace std;

static map<type_index, void*> lookup;

template<typename T> T* create(){
  static T* inst;
  auto const & type //must use a reference, as typeid has a private ctor
    = typeid(T);
  T* ret = static_cast<T*>(lookup[type]);
  if (ret) {
    cout<<"returning cached instance... won't create another instance of this type.\n";
    assert(inst == ret);
    return ret; 
  }
  ret= new T();
  lookup[type] = ret;
  inst = ret;
  return ret;
}
class C{
protected:
  C() {cout<<"C ctor, private\n";}
public:  
  ~C(){cout<<"C dtor, must be public to support delete\n";}
  friend C* create<C>();
};
class D: public C{
  D() {cout<<"D ctor, private, after calling base ctor\n";}
  friend D* create<D>();
};
int main(){
  auto ptr //asterisk is optional but better IMO 
    = create<C>();
  auto * ptrAgain = create<C>();
  assert(ptrAgain == ptr);
  
  auto * d = create<D>();
  auto * dAgain = create<D>();
  assert(dAgain == d);
  delete ptr;
}