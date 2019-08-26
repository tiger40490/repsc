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
long double const phi = 0.5 + 0.5*sqrt(5);
unsigned long long Fib(int N){
  long double ret = ( pow(phi,N) - pow(-phi, -N) )/sqrt(5);
  cout<<round(ret)<<" from formula\n";
  return round(ret);
}
int const N=70;
int main(){
	//Fibonacci Sequence is caluclated at Compile time 
  unsigned long long resultT = Fibonacci<N>::Val;
	cout << resultT << endl;
  assert (Fib(N) == resultT);
}/*Two ways to compute Fibonacci(N) at O(1) runtime complexity
*/