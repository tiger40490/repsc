/*
Note: dtor must be public to compile

showcase: a struct can extend a class, and vice versa
*/
#include <iostream>
using namespace std;

class base{
public: 
    //virtual
    ~base(){}
    //virtual
    void say(){cout<<"B.say()\n";}
};
struct derived: public base{
    virtual
    void say(){cout<<"D.say()\n";}
};
int main(){
    base* p = new derived();

    // prints DERIVED iFF "virtual" dtor; prints BASE otherwise, even with virtual say() in subclass !
    cout<<typeid(*p).name()<<endl; 
    p->say(); // ?
}/* demo use of typeid() without any vptr
*/