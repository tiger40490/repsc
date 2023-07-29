// todo: 

#include <iostream>
using namespace std;

struct A{
	~A(){cout<<"~A"; }
};
struct B: public A{
	virtual ~B(){cout <<"~B"; }
	//virtual keyword is not in base dtor, so base class lacks vptr 
};
int main3(){
	A *a=new B();
	delete a;
	return 0;
}
/////////////
struct Base{
	virtual void print(int x=1){
		cout<<"Base:" <<x;
	}
};
struct Derived: Base{
	virtual void print (int x=2){
		cout<<"Derived : "<<x;
	}
};
int main4(){
	Base *B = new Derived;
	B->print();
	return 0;
}
///////////
struct Base4{ 
  virtual ~Base4(){
    f(); // at this time, the subclass object is destructed, leaving behind a superclass object only.
	// virtual functions are non-virtual during ctor/dtor calls.
  }
  virtual void f(){cout<<"Base4::f\n";}
};
struct Der4: public Base4{ 
  ~Der4(){}
  virtual void f(){cout<<"Der4::f\n";}
};
int main(){
	Base4* basePtr = new Der4;
	delete basePtr;
	return 0;
}
