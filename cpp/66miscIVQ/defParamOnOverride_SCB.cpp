/*a SCB onsite question shared by Ashish

See open question below

*/
#include <iostream>
using namespace std;
struct B{ 
  virtual void print(int n=10){cout<<n<<" from B\n"; }
};
struct D1: public B{ 
  virtual void print(int n){cout<<n<<" from D1\n"; }
};
struct D2: public B{  
  virtual void print(int n=30){cout<<n<<" from D2\n"; }
};
template <typename Decl, typename Actual> test(){
  Decl * ptr = new Actual;
  ptr -> print();
}
int main(){
  test<B, D1>(); // prints 10
  //test<D1, D1>(); // won't compile, as I predicted
  test<D2, D2>(); // prints 30... as easily predictable
  test<B, D2>(); // prints 10 ... perhaps because def param is resolved at compile time??
}
