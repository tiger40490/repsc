// https://github.com/tiger40490/repo1/blob/cpp1/cpp/88miscLang/arrayNewDtor.cpp (??) shows simpler ways to test if a type is a ptr type, but techniques here are valuable at least in job interviews.
#include <assert.h>
#include <iostream>
using namespace std; 

struct type9{ char dummy[9]; }; //a 9-byte type

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
  int func1(ostream){return 0; }
  //float f2();
};

int main(void){
  typedef int * IntPtr;
  typedef long Foo::* FooMemberPtr;
  typedef int (Foo::*FooMemFunPtr)(ostream) ;
  FooMemFunPtr funPtr = Foo::func1;
  typedef int (*FuncPtr)();

  assert(1==isCustomPtr<IntPtr>::value); 
  assert(2==isCustomPtr<FuncPtr>::value);
  assert(4==isCustomPtr<FooMemberPtr>::value);
  assert(8==isCustomPtr<FooMemFunPtr>::value);
  assert(9==isCustomPtr<float>::value); //not a ptr at all
  cout<<"All tests passed";
}//based on https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE
