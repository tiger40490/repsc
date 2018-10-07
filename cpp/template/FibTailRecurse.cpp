//showcase compile time recursive template instantiation
//showcase template specialization
//showcase enum with a specific base type using a typedef
//showcase macro with arguments
#include <iostream>
#include <cassert>
#define check(N) assert (recurFunc(N) == FibCompileTime<N>::value);
using namespace std;

typedef long long fnum; //a Fib number

/* 0,1,1,2,3,5...
*/
fnum recurFunc(size_t distance, fnum first=0, fnum second=1){
	if (distance==0) return first;
	//cout<<first<<","<<second<<","<<distance<<endl;
	return recurFunc(distance-1, second, first+second);
}

// all 3 template params are non-type !
template <int DISTANCE, fnum A=0, fnum B=1> struct FibCompileTime{
    enum : fnum { //recursive computation is done at compile time
      value = FibCompileTime<DISTANCE-1, B, A+B>::value 
    };
};

//template specialization as a recursion exit condition
//Compiler would choose this specialized template when first template arg = 0
template <fnum A, fnum B> struct FibCompileTime<0, A, B> {
    enum : fnum { value = A };
};

int main(){
    check(91); //largest Fib number for long-long
    check(90);
}