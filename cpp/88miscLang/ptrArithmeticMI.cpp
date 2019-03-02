/*
demo 
*/
#include <stdio.h>
#include <stddef.h>
#include <iostream>
using namespace std;

struct A { 
  char age[3];
  funcWithoutRetType(long){return 0;}; 
};
struct B { 
  char age[7]; //same name!
  bf(int); 
};
struct C: public A, public B{};

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
int main(void) {
  basicPtrArithmetic();
  cout<<A().funcWithoutRetType(8)<<" <- default ret type is int\n";;
  cout<<sizeof(A)<<" = sizeof(A)"<<endl;
  cout<<sizeof(B)<<" = sizeof(B)"<<endl;
  cout<<sizeof(C)<<" = sizeof(C)"<<endl;
  C* pc = new C;
  cout<<(A*) pc<<" = A-object address\n";
  cout<<(B*) pc<<" = B-object address\n";
  cout<<     pc<<" = C-object address\n";
}/*demo of sizeof ^ ptr arithmetic
*/
