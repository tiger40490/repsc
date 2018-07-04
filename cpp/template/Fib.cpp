#include <iostream>
#include <cassert>
using namespace std;

template <int DISTANCE, int A=0, int B=1> struct Fibonacci{
    enum { 
      value = Fibonacci<DISTANCE-1, B, A+B>::value 
    };
};

//specialization: When distance to target value == 0, we have reached target ..
template <int A, int B> struct Fibonacci<0, A, B> {
    enum { value = A };
};

int main(){
    assert (2 == (Fibonacci<3>::value));
    assert (13 == (Fibonacci<7>::value));
    assert (8 == (Fibonacci<6>::value));
}