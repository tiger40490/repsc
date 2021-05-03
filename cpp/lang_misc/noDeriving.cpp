// showcase: calling ctor on stack to create an unnamed temp, then use it in a function call.
#include <iostream>
using namespace std;
class PoisonPill{
  friend class FinalClassPreCpp11;
  PoisonPill(){} //private ctor
};

struct FinalClassPreCpp11: virtual/*needed*/ PoisonPill{
// "virtual" inheritance forces Derived to call PoisonPill ctor DIRECTLY (short call stack), NOT using FinalClassPreCpp11 as an agent on a deeper call stack
  void show(){ cout<<"FinalClassPreCpp11"<<endl; }
};

struct Derived: public FinalClassPreCpp11{
  void show(){ cout<<"Derived"<<endl; }
};
int main(){  
  //Derived().show(); //breaks compiler if using "virtual" inheritance
  FinalClassPreCpp11().show();
}
/*Req: design an uninheritable class that we will instantiate as usual. 

See https://btv-gz.dreamhosters.com/wp-admin/post.php?post=40465&action=edit
*/