#include <iostream>

struct Trade{
    ~Trade()  {  throw 1; }
};

int main(){
  try {
	  Trade b;
		//throw 0; //crashing with or without this
	}
	catch ( int a ) {
	    std::cout << "Caught : " << a << std::endl;
	}
}/* https://bintanvictor.wordpress.com/2018/04/02/c11-dtorexception-rules-iv/ explains that c++11 assumes every dtor is a noexcept, so this code hits std::terminate()

Deepak gave me this code after a MS interview.
*/