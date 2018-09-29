//
#include <iostream>
#include <memory>
using namespace std;

struct C{
  virtual char type() const {return 'C' ;}
};
struct D : public C
{
  char type() const override {return 'D' ;}
};

template<typename T> struct smartPtr{
  smartPtr(T* arg) : raw(arg)
  {
    T* dummy = new T;
    cout<<"conversion ctor: from raw ptr of type "<<arg->type()<<" into smartPtr of "<<dummy->type()<<endl;
  }
  operator T*(){
    T* dummy = new T;
    cout<<"conversion operator to raw ptr of type "<<dummy->type()<<endl;
    return raw;
  }
  T* raw;
};

int main(){
  shared_ptr<D> dd(new D);
  shared_ptr<C> cc(dd);
  
  smartPtr<D> d2(new D);
  cout<<"now constructing smartPtr<C> from smartPtr<D>..\n";
  smartPtr<C> c2(d2);
}/* SCB-FM IV question: how is shared_ptr<Der> instance assignable to a shared_ptr<Base> variable when the two types are unrelated
*/