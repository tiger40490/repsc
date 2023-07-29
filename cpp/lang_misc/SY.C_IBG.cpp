// todo: 

#include <iostream>
using namespace std;
int main2(){
	int a=5;
	int b=0;
	int &r=a;
	r=b++;
	cout<<a<<r<<b;
	return 0;
}
/*
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
}*/
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
struct A{ 
  virtual ~A(){ f();}
  virtual void f(){cout<<"A::f\n";}
};
struct B: public A{ 
	~B(){}
  virtual void f(){cout<<"B::f\n";}
};
int main(){
	A* a=new B;
	delete a;
	return 0;
}
