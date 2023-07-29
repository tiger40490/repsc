// todo: 

#include <iostream>
using namespace std;

struct A{
	~A(){cout<<"~A"; }
};
struct B: public A{
	virtual ~B(){cout <<"~B"; }
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
	//cout<<c<<" "<<a;
	return 0;
}
///////////
struct Base4{ 
  virtual ~Base4(){ f();}
  virtual void f(){cout<<"Base4::f\n";}
};
struct Der4: public Base4{ 
	~Der4(){}
  virtual void f(){cout<<"Der4::f\n";}
};
int main(){
	Base4* a=new Der4;
	delete a;
	return 0;
}
