//todo: singleton
#include <typeindex>
#include <typeinfo>
#include <map>
#include <unordered_map>
#include <iostream>
#include <cassert>
using namespace std;

static map<type_index, void*> lookup;

template<typename T> T* create(){
  auto const & type //must use a reference as typeid ctor is private
    = typeid(T);
  if (lookup.count(type)) {
    cout<<"returning cached instance... won't create another instance of this type.\n";
    return (T*)lookup[type]; 
  }
  T* ret= new T();
  lookup[type] = ret;
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
  auto * ptrD = create<D>();
  delete ptr;
}