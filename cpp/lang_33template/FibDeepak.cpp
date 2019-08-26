/*
showcase empty tempate<> to create template specialization
*/
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

template <int N>
struct Fibonacci{
	static const unsigned long long Val = Fibonacci<N - 1>::Val + Fibonacci<N - 2>::Val;
};

template<>
struct Fibonacci<0>{
	static const unsigned long long Val = 0;
};
template<>
struct Fibonacci<1>{
	static const unsigned long long Val = 1;
};

////// formula method
typedef long double long_double_t;
long_double_t const phi = 0.5 + 0.5*sqrt(5);
unsigned long long Fib(int N){
  long_double_t b4rounding = ( pow(phi,N) - pow(-phi, -N) )/sqrt(5);
  unsigned long long ret = round(b4rounding);
  cout<<ret<<" from formula\n";
  return ret;
}
int const N=70; // beyond this value, the long double precision is no longer enough
int main(){
	//Fibonacci Sequence is caluclated at Compile time 
  unsigned long long resultT = Fibonacci<N>::Val;
	cout << resultT << endl;
  assert (Fib(N) == resultT);
}/*Two ways to compute Fibonacci(N) at O(1) runtime complexity
*/