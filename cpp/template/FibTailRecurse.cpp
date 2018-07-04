//showcase compile time recursive template instantiation
//showcase enum with a specific base typedef
//showcase macro
#include <iostream>
#include <cassert>
#define check(N) assert (recurs(N) == Fibonacci<N>::value);
using namespace std;

typedef long long fnum; //a Fib number

/* 0,1,1,2,3,5...
*/
fnum recurs(size_t distance, fnum first=0, fnum second=1){
	if (distance==0) return first;
	//cout<<first<<","<<second<<","<<distance<<endl;
	return recurs(distance-1, second, first+second);
}

template <int DISTANCE, fnum A=0, fnum B=1> struct Fibonacci{
    enum : fnum { //recursive computation is done at compile time
      value = Fibonacci<DISTANCE-1, B, A+B>::value 
    };
};

//specialization as a recursion exit
template <fnum A, fnum B> struct Fibonacci<0, A, B> {
    enum : fnum { value = A };
};

int main(){
    check(91); //largest Fib number for long long
    check(90);
}