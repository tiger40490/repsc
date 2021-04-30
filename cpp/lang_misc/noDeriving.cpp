// "virtual" inheritance forces Derived to call StopInheritance ctor directly. 
#include <iostream>
using namespace std;

class StopInheritance{
  friend class FinalClassPreCpp11;
  StopInheritance(){} //private ctor
};

struct FinalClassPreCpp11: virtual /*needed*/ StopInheritance{
  void Display(){
    cout<<" My FinalClassPreCpp11 Class"<<endl;
  }
};

struct Derived: public FinalClassPreCpp11{
  void Display(){
    cout<<" My derived Class"<<endl;
  }
};
int main(){  
  //Derived obj; //breaks compiler
  FinalClassPreCpp11 obj;
  obj.Display();
}
/*Req: design a class to be uninheritable but can be instantiated as usual. See https://btv-gz.dreamhosters.com/wp-admin/post.php?post=40465&action=edit

*/