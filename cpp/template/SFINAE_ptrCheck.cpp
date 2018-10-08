//showcase std::is_pointer<T> is_member...<T> etc
//showcase static_assert vs assert
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std; 

struct type9{ char dummy[9]; }; //a 9-byte type

template <class T> struct isCustomPtr{
  template <class U=T> //with or without "=T"  U would get set to T when compiler evaluates sizeof(f281(aFieldOfType_T))
  static char f281(U *); //without U this becomes non-templ-func-in-class-templ..no SFINAE !

  template <class U=T>
  static short f281(U (*)());

  template <class X, typename ARG=T> // =T is optional documentation, probably ignored by compiler
  static float f281(ARG  X::*);

  template <class X, typename ARG=T>
  static double f281(ARG (X::*)(ostream));

  static type9 f281(...); //default overload
  static T* aFieldOfType_T; //I prefer pointer because T may not be constructible
  static size_t const value = sizeof(f281(*aFieldOfType_T));
  static bool const isSimplePtr = std::is_pointer<T>::value;
};

struct Foo {
  long bar; 
  int func1(ostream){return 0; }
};

int main(void){
  typedef int * IntPtr;
  typedef long Foo::* FooMemberPtr;
  typedef int (Foo::*FooMemFunPtr)(ostream) ;
  FooMemFunPtr funPtr = Foo::func1;
  typedef int (*FuncPtr)();

  static_assert(1==isCustomPtr<IntPtr>::value); 
  static_assert(isCustomPtr<IntPtr>::isSimplePtr);

  static_assert(2==isCustomPtr<FuncPtr>::value);
  static_assert(isCustomPtr<FuncPtr>::isSimplePtr);

  static_assert(4==isCustomPtr<FooMemberPtr>::value);
  static_assert(is_member_pointer<FooMemberPtr>::value);

  static_assert(8==isCustomPtr<FooMemFunPtr>::value);
  static_assert(is_member_function_pointer<FooMemFunPtr>::value);

  static_assert(9==isCustomPtr<float>::value); //not a ptr at all
  static_assert( ! isCustomPtr<float>::isSimplePtr); 
  
  //static_assert(vector<int>().size() == 0); //won't compile
  assert(vector<int>().size() == 0);
  cout<<"All tests passed";
}//based on https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE
// https://github.com/tiger40490/repo1/blob/cpp1/cpp/88miscLang/arrayNewDtor.cpp (??) shows simpler ways to test if a type is a ptr type, but techniques here are valuable at least in job interviews.
