#include <stdio.h> 
#include <assert.h>
#include <string>
using namespace std;
struct B1 { int b1; virtual ~B1() {} }; 
struct B2 { int b2; virtual ~B2() {} }; 
struct D: B1, B2 {
  int d;
  ~D(){printf("~D\n"); }
}; 
void upCastTest(){
  D * const pd = new D; 
  B1 *ptr1 = pd;
  assert((void*)pd == (void*)ptr1 && "1st base subobject has zero offset from the subclass object"); 

  B2 *ptr2 = pd; 
  printf("pd=%p, ptr1 = %p, ptr2= %p\n", pd, ptr1, ptr2);
  assert((void*)pd != (void*)ptr2 && "2nd base subobject has an offset from the subclass object");
  delete ptr2; //even though ptr2 is unequal to pd, ~D still gets invoked.
}
void downCastTest(){
  string * dummy = new string; //just to avoid allocating to the same address
  B2 * const ptr2 = new D; 
  D  *pd   = dynamic_cast<D*>(ptr2);
  assert((void*)pd != (void*)ptr2 && "2nd base subobject has an offset from the subclass object");

  B1 *ptr1 = pd; 
  printf("pd=%p, ptr1 = %p, ptr2= %p\n", pd, ptr1, ptr2);
  assert((void*)pd == (void*)ptr1 && "1st base subobject has zero offset from the subclass object"); 
  delete dummy;
  delete ptr2; //even though ptr2 is unequal to pd, ~D still gets invoked.
}
int main() { 
  upCastTest();
  downCastTest();
} 
/* Program to demo that down-cast or implicit up-cast an original address can produce a different address
*/