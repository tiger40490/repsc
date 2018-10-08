#include <assert.h>
#include <iostream>
#include <type_traits>
using namespace std; 

class Trade{};
template <typename ANY> struct List{
  template<class T> //default 
  enable_if_t<   is_pointer<T>::value, T> 
  insert(T t){
    static_assert(is_pointer<ANY>::value);
    static_assert(is_pointer<T>::value);
    cout << "insert pointer" << endl;
  }

  template<class T>
  enable_if_t< ! is_pointer<T>::value, T> 
  insert(T t){
    static_assert( !is_pointer<ANY>::value);
    static_assert( !is_pointer<T>::value);
    cout << "insert non-pointer" << endl;
  }
};
template<typename T>
enable_if_t<is_pointer<T>::value, //compile-time boolean
           T> //return type is T
play(T t){
    static_assert(is_pointer<T>::value);    
    cout<<"arg is a pointer\n";
    return nullptr;
}
int main(){
    play(new int);
        
    List<Trade> li;
    List<Trade*> ptrLi;

    li.insert(Trade());
    //li.insert(new Trade()); //won't compile
    ptrLi.insert(new Trade());
    //ptrLi.insert(Trade()); //won't compile
}//based on https://stackoverflow.com/questions/30556176/template-detects-if-t-is-pointer-or-class
