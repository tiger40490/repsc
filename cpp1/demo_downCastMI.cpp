#include <iostream>
using namespace std;

struct B1{
  int f1; //without this field, all 3 addresses are identical
};
struct B2{
  int f2; //without this field, all 3 addresses are identical
};
struct D: public B1, B2{} der;
int main(){
  cout<<&der<<" = addr of derived object \n";
  cout<<dynamic_cast<B1*>(&der)<<" = addr after casting to B1* \n"; //same as above
  cout<<dynamic_cast<B2*>(&der)<<" = addr after casting to B2* \n"; //different
}
/* Q: dynamic_cast always gives the same address?
   A: not always. Consider MI.
   A: if one of the two base classes is a pure-interface (i.e. no instance field) then YES
*/
