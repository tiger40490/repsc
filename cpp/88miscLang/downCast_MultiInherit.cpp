//todo: sfinae
#include <iostream>
#include <assert.h>
using namespace std;

struct B1empty{};
struct B2empty{};
struct B1nonEmpty{
  int f1; //without this field, all 3 object addresses are identical
};
struct B2nonEmpty{
  int f2; //without this field, all 3 object addresses are identical
};
template<typename B1, typename B2, char mode>
struct D: public B1, B2{
  test(){
    auto pb1 = dynamic_cast<B1*>(this);
    auto pb2 = dynamic_cast<B2*>(this);
    cout<<(int)mode<<" <===== new mode in a new test\n";
    cout<<this<<" = addr of derived object \n";
    cout<<pb1<<" = addr after casting to B1* \n"; //same as der
    cout<<pb2<<" = addr after casting to B2* \n"; //different from der
    assert((void*)pb1==(void*)this);
    
    if     (mode == 2)
      assert((void*)pb2!=(void*)this);
    else if (mode <= 1)
      assert((void*)pb2==(void*)this);
    else 
      assert(1==0);
  }
};
int main(){
  D<B1nonEmpty, B2nonEmpty, 2>().test();
  D<B1empty, B2nonEmpty, 1>().test();
  D<B1nonEmpty, B2empty, 1>().test();
  D<B1empty, B2empty, 0>().test();
}/* Q: dynamic_cast always(?) gives the same address?
   A: not always. Consider MI.
   A: if any one of the two base classes is a pure-interface (i.e. no instance field) then YES
*/