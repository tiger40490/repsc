/*
showcase pointer arithmetic uses sizeof(declared type)
showcase create a dummy class with a target sizeof
showcase function declaration without return type .. defauls to int
showcase pointer subtraction result can be a correct negative value
*/
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <iostream>
using namespace std;

void basicPtrArithmetic() {
    int a[20] = {0};
    int *p = &a[3];
    int *q = &a[13];
    ptrdiff_t diff1 = q - p; // This is 10
    char *x = (char*)p;
    char *y = (char*)q;
    ptrdiff_t diff2 = y - x; // This is 10 times sizeof(int)
    printf("diff1=%d, diff2=%d\n", (int)diff1, (int)diff2);
}
struct B1 { char nickname[3];
  funcWithoutRetType(long){return 0;}; 
};
struct B2 { char nickname[7]; /*same name*/ };
struct C: public B1, public B2{};
int main(void) {
  basicPtrArithmetic();
  cout<<B1().funcWithoutRetType(8)<<" <- implicit return type is int\n";
  C* pc = new C;

  cout<<sizeof(B1)<<" = sizeof(B1)"<<endl;
  cout<<  (B1*) pc<<" = B1 sub-object address\n";
  cout<<1+(B1*) pc<<" = incremented\n";

  cout<<sizeof(B2)<<" = sizeof(B2)"<<endl;
  cout<<  (B2*) pc<<" = B2 sub-object address\n";
  cout<<1+(B2*) pc<<" = incremented\n";
  cout<<2+(B2*) pc<<" = incremented again\n";

  cout<<sizeof(C)<<" = sizeof(C)"<<endl;
  cout<<  pc<<" = C object address (same as B1)\n";
  cout<<1+pc<<" = incremented\n";
  
  auto ptrSubtraction = (char*)pc - (char*)(B2*)pc; //won't compare without cast
  cout<< ptrSubtraction<<" = addr diff #negative because B2 sub-object has higher address than B1 i.e. C \n";
  assert(ptrSubtraction == -1 * (int)sizeof(B1));
}/*
demo of pointer casting in Multiple Inheritance context.
demo sizeof ^ ptr arithmetic
*/
