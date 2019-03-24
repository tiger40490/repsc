#include <iostream>
#include <assert.h>
using namespace std;

struct B1f{
  int f1; //without this field, all 3 object addresses are identical
};
struct B2f{
  int f2; //without this field, all 3 object addresses are identical
};
#define B1 B1f
#define B2 B2f
struct D: public B1, B2{} der;
int testWithFields(){
  auto pd = &der;
  auto pb1 = dynamic_cast<B1*>(pd);
  auto pb2 = dynamic_cast<B2*>(pd);
  cout<<pd<<" = addr of derived object \n";
  cout<<pb1<<" = addr after casting to B1* \n"; //same as der
  cout<<pb2<<" = addr after casting to B2* \n"; //different from der

  assert((void*)pb1==(void*)pd);
  assert((void*)pb2!=(void*)pd);
}
////////
struct B1empty{
  //int f1; //without this field, all 3 object addresses are identical
};
struct B2empty{
  ///int f2; //without this field, all 3 object addresses are identical
};
#define B1 B1empty
#define B2 B2empty
int testWithoutFields(){
  auto pd = &der;
  auto pb1 = dynamic_cast<B1*>(pd);
  auto pb2 = dynamic_cast<B2*>(pd);
  cout<<pd<<" = addr of derived object \n";
  cout<<pb1<<" = addr after casting to B1* \n"; //same as der
  cout<<pb2<<" = addr after casting to B2* \n"; //different from der

  assert((void*)pb1==(void*)pd);
  assert((void*)pb2!=(void*)pd);
}
int main(){
  testWithFields();
}/* Q: dynamic_cast always(?) gives the same address?
   A: not always. Consider MI.
   A: if any one of the two base classes is a pure-interface (i.e. no instance field) then YES
*/
