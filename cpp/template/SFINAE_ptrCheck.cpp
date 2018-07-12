#include <assert.h>
#include <iostream>
using namespace std; 

struct type9{ char dummy[9]; };
template <class T> struct isCustomPtr{
  template <class U>
  static char f281(U *); //U can be int

  template <class U>
  static short f281(U (*)());

  template <class X, class Y>
  static float f281(Y  X::*);

  template <class X, class Y>
  static double f281(Y (X::*)(ostream));

  static type9 f281(...); //default overload
  static T t;
  static size_t const value = sizeof(f281(t));
};

struct Foo {
  long bar; 
  int f1(ostream);
  //float f2();
};

int main(void){
  typedef int * IntPtr;
  typedef long Foo::* FooMemberPtr;
  typedef int (Foo::*FooMemFunPtr)(ostream) ;
  typedef int (*FuncPtr)();

  assert(1==isCustomPtr<IntPtr>::value); 
  assert(2==isCustomPtr<FuncPtr>::value);
  assert(4==isCustomPtr<FooMemberPtr>::value);
  assert(8==isCustomPtr<FooMemFunPtr>::value);
  cout<<isCustomPtr<float>::value;
}//based on https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE
