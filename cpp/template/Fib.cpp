#include <iostream>
#include <cassert>
using namespace std;

template <int T> struct Fibonacci{
    enum { 
      value = (Fibonacci<T - 1>::value + Fibonacci<T - 2>::value) 
    };
};

//specializations
template <> struct Fibonacci<0> {
    enum { value = 0 };
};

template <> struct Fibonacci<1> {
    enum { value = 1 };
};

int main(){
    assert (13 == Fibonacci<7>::value);
    assert (8 == Fibonacci<6>::value);
}