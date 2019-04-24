/*The misspelling in move ctor is undetected by compiler. 
If I declare copier as delete, then compiler complains on deleted copier
*/
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
struct Payload{
  Payload(){cout<<"Payload ctor\n"; }
};
struct Wrapper1{
  Wrapper1(){cout<<"Wrapper1 ctor\n"; }  
  Wrappppppppper1(Wrapper1 && rhs){
	cout<<"Wrapper1 move ctor\n"; 
  }
  Wrapper1(Wrapper1 const & rhs) // = delete; 
  { cout<<"Wrapper1 copy ctor\n"; }
};
void testMove(Wrapper1 && rhs){
  cout<<"testMove\n";
  Wrapper1 local=move(rhs);
}
int main(){
  Wrapper1 w;
  testMove(move(w));
  return 0;
}
