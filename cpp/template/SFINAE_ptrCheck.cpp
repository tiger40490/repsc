//showcase std::is_pointer<T> is_member...<T> etc
//showcase static_assert vs assert
//todo: pass ptr to member instead of nullptr
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std; 
struct Foo {
  long bar; 
  int func1(ostream){return 0; }
} foo;
using FooMemberPtr = long Foo::*;

struct type9{ char dummy[9]; }; //a 9-byte type

template <class T> struct isCustomPtr{
  template <class U> //U would get set to T when compiler evaluates sizeof(f281(aFieldOfType_T))
  static char f281(U *){ //without U this becomes non-templ-func-in-class-templ..no SFINAE !
      static_assert(is_same<U*,T>::value);
      return 0;
  }  
  template <class U>
  static short f281(U (*)()){
      static_assert(is_same<U(*)(), T>::value);
      return 0;
  }
  template <class X, typename ARG=T> 
  static float f281(ARG X::*){
      static_assert(is_same<ARG, long>::value);
      static_assert(is_same<X, Foo>::value);
      static_assert(is_same<ARG X::*, T>::value);
      return 0;
  }

  template <class X, typename ARG>
  static double f281(ARG (X::*)(ostream));

  static type9 f281(...); //default overload
  static T* aFieldOfType_T; //I prefer pointer because T may not be constructible
  static size_t const value = sizeof(f281(*aFieldOfType_T));
  static bool const isSimplePtr = std::is_pointer<T>::value;
};
//template <class T> template <class U> char isCustomPtr<T>::f281(U *)//showcase the messy syntax
int main(void){
  typedef int * IntPtr;
  typedef int (Foo::*FooMemFunPtr)(ostream) ;
  FooMemFunPtr funPtr = Foo::func1;
  typedef int (*FuncPtr)();

  static_assert(1==isCustomPtr<IntPtr>::value); 
  static_assert(isCustomPtr<IntPtr>::isSimplePtr);
  isCustomPtr<IntPtr>::f281(new int);

  static_assert(2==isCustomPtr<FuncPtr>::value);
  static_assert(isCustomPtr<FuncPtr>::isSimplePtr);
  isCustomPtr<FuncPtr>::f281(static_cast<FuncPtr>(nullptr));

  static_assert(4==isCustomPtr<FooMemberPtr>::value);
  static_assert(is_member_pointer<FooMemberPtr>::value);
  isCustomPtr<FooMemberPtr>::f281((FooMemberPtr)nullptr);

  static_assert(8==isCustomPtr<FooMemFunPtr>::value);
  static_assert(is_member_function_pointer<FooMemFunPtr>::value);

  static_assert(9==isCustomPtr<float>::value); //not a ptr at all
  static_assert( ! isCustomPtr<float>::isSimplePtr); 
  
  //static_assert(vector<int>().size() == 0); //won't compile
  assert(vector<int>().size() == 0);
  cout<<"All tests passed";
}//based on https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/SFINAE
// https://github.com/tiger40490/repo1/blob/cpp1/cpp/88miscLang/arrayNewDtor.cpp (??) shows simpler ways to test if a type is a ptr type, but techniques here are valuable at least in job interviews.
