#include <iostream>
#include <cassert>
using namespace std;

struct B{
  virtual char play(){
    cout<<"B::play()\n"; 
    return 'B';
  }
};
struct C: public B{
  virtual char play(){
    cout<<"C::play()\n"; 
    return 'C';
  }    
};
int main(){
  B* ptr = new C();
  assert ('C' == C().play());
  assert ('B' == ptr->B::play()); // java can't invoke a superclass method via a subclass instance
  
  // compiler can choose to inline the above, but not the below
  assert ('C' == ptr->play()); //the most common usage of a given virtual function provided by 3rd party.
}
/* Illustrates a few syntax tweaks to allow compiler to inline virtual function calls. Basically, you the programmer pin down exactly which version of the function definition (subclass or baseclass) to use at the call site. You then communicate that with enouth clarity to the compiler.

By default virtual function calls are not inlined.
*/