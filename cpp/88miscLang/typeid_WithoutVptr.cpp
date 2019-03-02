/*
Note: dtor must be public to compile

showcase: a struct can extend a class, and vice versa
*/
#include <iostream>
using namespace std;

class base{
public: 
    virtual
    ~base(){}
};
struct derived: public base{};
int main(){
    base* p = new derived();
    cout<<typeid(*p).name(); // prints DERIVED if "virtual"; prints BASE otherwise  
}/*
*/