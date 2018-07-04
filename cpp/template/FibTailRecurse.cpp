#include <iostream>
#include <cassert>
using namespace std;

typedef int fnum; //a Fib number

/* 0,1,1,2,3,5...
*/
recurs(size_t distance, fnum first=0, fnum second=1){
	if (distance==0) return first;
	//cout<<first<<","<<second<<","<<distance<<endl;
	return recurs(distance-1, second, first+second);
}

template <int DISTANCE, fnum A=0, fnum B=1> struct Fibonacci{
    enum { 
      value = Fibonacci<DISTANCE-1, B, A+B>::value 
    };
};

//specialization
template <fnum A, fnum B> struct Fibonacci<0, A, B> {
    enum { value = A };
};

int main(){
    assert (recurs(3)  == (Fibonacci<3>::value));
    assert (recurs(7) == (Fibonacci<7>::value));
    assert (recurs(6)  == (Fibonacci<6>::value));
}