/*Showcase Two ways to use enable_if_t<...> as a proper Type. I think enable_if_t is always used as a Type, never as a function or variable or class.

1) programmer to specify an optional 2nd type arg like enable_if_t<... , AAA> so if type check passes, then enable_if_t is an alias of AAA

2) use enable_if_t<...>* as a type, which evaluates to the void pointer type. This is because enable_if_t has its 2nd type arg default to void. You can't use void as a type, but void pointer is a proper type.
*/
#include <iostream>
#include <type_traits>
using namespace std; 

template<typename T>
enable_if_t<is_pointer<T>::value, //compile-time boolean
  T> //fexp() return type is T because enable_if_t<true, U> is an alias of U
fexp(T t){
    static_assert(is_pointer<T>::value);
    cout<<*t<<"\n";
    return nullptr;
}

template<typename T>
enable_if_t<is_pointer<T>::value> //compile-time boolean
  * //fvoidP() return type is void ptr because enable_if_t<true> evaluates to void
fvoidP(T t){
    static_assert(is_pointer<T>::value);
    cout<<*t<<"\n";
    return nullptr;
}

int main(){
    fexp(new int(2));
    fvoidP(new int(10));
    //fvoidP(333); //Won't compile. This overload is removed by enabled_if
}//My own experiment, not based on online code