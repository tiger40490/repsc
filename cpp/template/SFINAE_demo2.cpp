#include <assert.h>
#include <iostream>
#include <sstream>
//using namespace std; //problematic

struct type9{ char dummy[9]; };
template <class T> struct is_pointer{
  template <class U>
  static char is_ptr(U *); //U can be int

  template <class U>
  static short is_ptr(U (*)());

  template <class X, class Y>
  static float is_ptr(Y  X::*);

  template <class X, class Y>
  static double is_ptr(Y (X::*)(std::stringstream));

  static type9 is_ptr(...); //default overload
  static T t;
  static size_t const value = sizeof(is_ptr(t));
};

struct Foo {
  long bar; 
  int f1(std::stringstream);
  //float f2();
};

int main(void){
  typedef int * IntPtr;
  typedef long Foo::* FooMemberPtr;
  typedef int (Foo::*FooMemFunPtr)(std::stringstream) ;
  typedef int (*FuncPtr)();

  assert(1==is_pointer<IntPtr>::value); 
  assert(2==is_pointer<FuncPtr>::value);
  assert(4==is_pointer<FooMemberPtr>::value);
  assert(8==is_pointer<FooMemFunPtr>::value);
  std::cout<<is_pointer<float>::value;
}//based on https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE
