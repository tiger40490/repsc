/*showcase {} usage in field initializer
*/
#include<iostream>
using namespace std;
struct S {
	int length;
	int* ptr; // int array on heap, owned by this instance not shared.
    S(int px = 1) : 
	  length{ px },  ptr{new int[length]} { cout << "S()\n";  }
	
	~S() {
		delete [] ptr;
		cout << "~S()\n";	
	}
	S& operator=( S const & other) {
	  if (&other != this) {
		length = other.length;
		delete [] ptr;
		ptr = new int[length]; 
		// copy content from other.ptr
		cout << "op=\n";
	  }
	  return *this;
	}
	S(S const & other) : length{ other.length }, ptr{new int[length]} { 
	  // copy content from other.ptr
	  cout << "cp-ctor\n"; 
	}
	S& operator=(S&& other) {
	  if (&other != this) {		
		delete[] ptr;
		length = other.length;
		ptr = other.ptr;
		other.ptr = nullptr;
		cout << "S& operator=(S&& other)\n";
	  }
	  return *this;
	}
	S(S&& other) : length{ other.length }, ptr{ other.ptr }  { other.ptr = nullptr;	cout << "S(S&& other)\n";	} 
};
S IncrementIdAndReturnByRvRef(S&& src) { src.length++; 	return src; }

S IncrementIdAndReturnByRef(const S& src) { 	return src; }

S GetS() { return S(); }

int main(){
	S s;
	S obj(s); //Copy constructor
	S obj0(move(s)); // I do not need s anymore
	S obj1 = GetS();  //move elison RVO
	S obj2 (GetS()); //Move elison RVO
	S obj3 (move(GetS()));  //move constructor. Obj2 construction is more performant than this. 
	obj2 = GetS(); //Call move assigmemnt operator to assign temporary/dying/expiring value to the obj2. 
	auto a = IncrementIdAndReturnByRvRef(GetS());
	auto b = IncrementIdAndReturnByRef(GetS()); // Temporary cannot be modified without const_cast
	cout << a.length << " " << b.length << endl;
}
/* Modified from demo program from my friend Ashish.
*/