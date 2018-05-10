#include <stdio.h>

template <class T>
struct is_pointer{
  template <class U>
  static char is_ptr(U *);

  template <class X, class Y>
  static char is_ptr(Y X::*);

  template <class U>
  static char is_ptr(U (*)());

  static double is_ptr(...);

  static T t;
  enum { value = sizeof(is_ptr(t)) == sizeof(char) };
};

struct Foo {int bar; };

int main(void){
  typedef int * IntPtr;
  typedef int Foo::* FooMemberPtr;
  typedef int (*FuncPtr)();

  printf("%d\n",is_pointer<IntPtr>::value);        // prints 1
  printf("%d\n",is_pointer<FooMemberPtr>::value);  // prints 1
  printf("%d\n",is_pointer<FuncPtr>::value);       // prints 1
}//based on https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE
