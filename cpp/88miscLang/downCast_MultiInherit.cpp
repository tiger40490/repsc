#include <iostream>
#include <assert.h>
using namespace std;

struct B1{
  int f1; //without this field, all 3 object addresses are identical
};
struct B2{
  int f2; //without this field, all 3 object addresses are identical
};
struct D: public B1, B2{} der;
int main(){
  auto pd = &der;
  cout<<pd<<" = addr of derived object \n";
  cout<<dynamic_cast<B1*>(pd)<<" = addr after casting to B1* \n"; //same as der
  assert((void*)dynamic_cast<B1*>(pd)==(void*)pd);
  cout<<dynamic_cast<B2*>(pd)<<" = addr after casting to B2* \n"; //different from der
  assert((void*)dynamic_cast<B2*>(pd)!=(void*)pd);
}
/* Q: dynamic_cast always(?) gives the same address?
   A: not always. Consider MI.
   A: if any one of the two base classes is a pure-interface (i.e. no instance field) then YES
*/
