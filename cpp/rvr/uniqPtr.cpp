/*
*/
#include <iostream>
#include <memory>
using namespace std;

class Obj{
	char value;
public:
	void update(const char & str) { value = str;  }
	void print() { cout << "Value : " << value << endl; }
};

unique_ptr<Obj> func(unique_ptr<Obj> ptr){
	ptr->update('h');
	return ptr;  
  //Deepak said .. This is automatically converted to Rvalue Reference.
  //EffectiveModernC++ P176 says that in this situation, compiler can't use RVO so it must apply implicit std::move() and return a Rvalue Reference
}

int main(){
	unique_ptr<Obj> ptr=make_unique<Obj>();
	unique_ptr<Obj> nPtr =  func( move(ptr) );//std::move() needed to compile
	nPtr->print();
}/*Deepak's demo of mover semantics
*/