/*
showcase empty tempate<> to create template specialization
*/
#include <iostream>
template <int N>
struct Fibonacci{
	static const long long Val = Fibonacci<N - 1>::Val + Fibonacci<N - 2>::Val;
};

template<>
struct Fibonacci<0>{
	static const int Val = 0;
};

template<>
struct Fibonacci<1>{
	static const int Val = 1;
};

int main(){
	//Fibonacci Sequence is caluclated at Compile time 
	std::cout << Fibonacci<92>::Val << std::endl;
}