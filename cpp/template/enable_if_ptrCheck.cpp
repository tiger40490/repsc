#include <assert.h>
#include <iostream>
#include <type_traits>
using namespace std; 

class MyClass{};
template <typename ANY> struct List{
  template<class T=ANY> //?
  void insert(T t, typename enable_if<  is_pointer<T>::value >::type* = 0){
        cout << "insert pointer" << endl;
  }

  template<class T=ANY>
  void insert(T t, typename enable_if< !is_pointer<T>::value >::type* = 0){
        cout << "insert non-pointer" << endl;
  }
};

int main(){
    MyClass a;

    List<MyClass> lst;
    List<MyClass*> plst;

    lst.insert(a);
    plst.insert(new MyClass());

    return 0;
}//based on https://stackoverflow.com/questions/30556176/template-detects-if-t-is-pointer-or-class
