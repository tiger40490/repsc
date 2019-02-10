#include <iostream>
#include <type_traits>
#include <limits>
#include <cmath>

//For floating type's, the below function will be used to generate the functions
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
Equals( T lhs, T rhs ){
	std::cout << "Floating type comparision" << std::endl;
	return std::abs( lhs - rhs )<0.01;
}

//For all other types although the condition fails (!is_floating_type), it does not result in Error.i.e. 'char' != '!(floating_point)'
//But this does not result in error. Instead, it simply uses the below function to generate Code for all other Types
template <typename T>
//typename std::enable_if<std::is_integral<T>::value, bool>::type
typename std::enable_if<!std::is_floating_point<T>::value, bool>::type
Equals( T lhs, T rhs ){
	std::cout << "Non-float type comparision" << std::endl;
	return lhs == rhs;
}

int main(){
	float a = 1.0, b = 1.0001;
	if ( Equals<float>(a , b ) ) 	{
		std::cout << "Both float points are Equal " << std::endl;
	}	else	{
		std::cout << "Both float points are NOT Equal " << std::endl;
	}

	int x = 1, y = 2;
	if ( Equals<int>( x , y ) ) {
		std::cout << "Both integers are Equal " << std::endl;
	}	else	{
		std::cout << "Both Integers are NOT Equal " << std::endl;
	}
}/*simple demo by Deepak
*/