//technique: enum nested in a class template
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
fnum recurFunc(size_t distance, fnum distantAncestor1=0, fnum distantAncestor2=1){
    if (distantAncestor1==0){
        cout<<distance<<" is original input to recurFunc\n";
    }
    if (distance==0) {
        cout<<distantAncestor1<<" is result from recurFunc\n";
        return distantAncestor1;
    }
    //cout<<distantAncestor1<<","<<distantAncestor2<<","<<distance<<endl;
    return recurFunc(distance-1, distantAncestor2, distantAncestor1+distantAncestor2);
}
// all 3 template params are non-type !
template <int DISTANCE, fnum A=0, fnum B=1> struct FibCompileTime{
    enum : fnum { //recursive computation is done at compile time
      value = FibCompileTime<DISTANCE-1, B, A+B>::value 
    };
};

//template specialization as a recursion exit condition
//Compiler would choose this specialization when first template arg i.e. DISTANCE = 0
template <fnum A, fnum B> struct FibCompileTime<0, A, B> {
    enum : fnum { value = A };
};

int main(){
    check(91); //largest Fib number for long-long
    check(90);
}