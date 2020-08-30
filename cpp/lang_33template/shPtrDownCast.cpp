/* 
Can use typeid(..).name but if no virtual function, then my home-grown solution "this->dynamic_type" is needed.
*/
#include <iostream>
#include <memory>
using namespace std;

struct A {
  static const char* static_type;
  const char* dynamic_type;
  A() { dynamic_type = static_type; }
  virtual ~A(){}; //without this, the downCast won't compile
};
struct D: A {
  static const char* static_type;
  D() { dynamic_type = static_type; }
  virtual ~D(){}; //even with this, the downCast still won't compile
};

const char* A::static_type = "class A";
const char* D::static_type = "class D";

int main () {
  shared_ptr<D> const dabao = make_shared<D>();
  shared_ptr<A> foo = dabao; // no cast needed. See explanation in shPtrUpcastCopy.cpp
  
  cout << "foo's static  type: " << foo->static_type << '\n'; //A
  cout << "foo's dynamic type: " << foo->dynamic_type << '\n'; //D

  A* rawA =new A;
  
  //both dynamic_cast and dynamic_pointer_cast fail without the a virtual func in base class
  D* rawD =dynamic_cast<D*>(rawA); 
  //cout << "rawD's dynamic type: " << rawD->dynamic_type << '\n'; //runtime error
  
  //shared_ptr<D> downCast = dynamic_pointer_cast<D>(make_shared<A>());
  
  //Both dynamic_cast and dynamic_pointer_cast above fail at RUNtime as compiler misses the issue completely
  
  shared_ptr<D> downCast = dynamic_pointer_cast<D>(foo);
  cout << "downCast's dynamic type: " << downCast->dynamic_type << '\n'; 
  
  return 0;
}
/* In all the successful tests, the actual payload object on heap is always some D instance, never a base class instance. Also, a virtual function in base class is required.
Downcast is performed only after an upcast.

When the payload is an A instance, the downcast fails.
*/
