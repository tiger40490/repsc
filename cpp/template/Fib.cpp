#include <iostream>
#include <cassert>
using namespace std;

typedef int fn; //a Fib number

/* 0,1,1,2,3,5...
recurs(0,1,0) == 0
recurs(0,1,1) == 1
*/
recurs(size_t distance, fn first=0, fn second=1){
	if (distance==0) return first;
	//cout<<first<<","<<second<<","<<distance<<endl;
	return recurs(distance-1, second, first+second);
}

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
    assert (recurs(3)  == (Fibonacci<3>::value));
    assert (recurs(7) == (Fibonacci<7>::value));
    assert (recurs(6)  == (Fibonacci<6>::value));
}