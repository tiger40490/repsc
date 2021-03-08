/*showcase braces {} used in field initializers of constructors
*/
#include<iostream>
using namespace std;
int lastId=100;
struct S { //This class holds a large array as an expensive resource. Move operators steal this resource to avoid expensive allocation and copying.
	int const id;
	int length; //without saving the original length, it's impossible to recover the initial size of array-new
	int* ptr; // int array on heap, owned by this instance not shared.
    S(int px = 1000) : id{++lastId}, length{ px },  ptr{new int[length]} { cout << "S() for "<<id<<"\n";  }
	
	~S() {
		delete [] ptr;
		cout << "~S() for "<<id<<"\n";	
	}
	S& operator=( S const & other) {
	  if (&other != this) {
		length = other.length;
		
		delete [] ptr;
		ptr = new int[length]; 
		// copy content from other.ptr
		cout << "op=() from "<<other.id<<"n";
	  }
	  return *this;
	}
	//explicit 
	S(S const & other) : id{++lastId}, length{ other.length }, ptr{new int[length]} { 
	  // copy content from other.ptr
	  cout << "cp-ctor from "<<other.id<<"\n"; 
	}
	
	// now the move facilities:
	S& operator=(S&& other) {
	  if (&other != this) {		
		delete[] ptr;
		length = other.length;
		ptr = other.ptr;
		other.ptr = nullptr;
		cout << "S& operator=(S&& other) from "<<other.id<<"\n";
	  }
	  return *this;
	}
	S(S&& other) : id{++lastId}, length{ other.length }, ptr{ other.ptr }  { other.ptr = nullptr;	cout << "S(S&& other) from "<<other.id<<"\n";	} 
};
S truncateByRVR(S&& src) { 
  --src.length; // src instance is still usable until now
  return move(src); // src is now used in a move-construction, iFF you use std::move()
}

S truncateByConstRef(S const& src) { 
 S ret(src); 
 --ret.length;
 return ret;
}
S GetS() { return S(); }

int main(){
	S obj9;
	S obj(obj9); //Copy constructor
	S obj0(move(obj9)); // I do not need obj9 anymore
	S obj1 = GetS();  //RVO
	cout<<33333<<endl;
	S obj2 (GetS()); //RVO
	cout<<4444<<endl;
	S obj3 (move(GetS()));  //move constructor. Obj2 construction (RVO) is more efficient than this. 
	cout<<5555<<endl;
	obj2 = GetS(); //Call move assigmemnt operator to assign temporary/dying/expiring value to the obj2. 
	cout<<6666<<endl;
	
	auto a = truncateByRVR(GetS());
	cout<<7777<<endl;
	
	auto b = truncateByConstRef(GetS()); 
	cout << a.length << " " << b.length << endl;
}
/* Modified from demo program from my friend Ashish.
*/