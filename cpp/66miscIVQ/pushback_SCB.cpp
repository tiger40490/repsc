/*a SCB onsite question shared by Ashish

showcase field initializer on field declaration, outside the constructor ... Not possible before c++11

Q: why is push_back() always calling the copy ctor?
*/
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
struct Payload{
  Payload(){cout<<"Payload ctor\n"; }
};
struct Wrapper1{
  shared_ptr<Payload> sp=make_shared<Payload>();
  Wrapper1(){cout<<"Wrapper1 ctor\n"; }  
  Wrapper1(Wrapper1 && rhs){
	cout<<"Wrapper1 move ctor\n"; 
	this->sp = rhs.sp;
  }
  Wrapper1(Wrapper1 const & rhs) 
  : sp(rhs.sp){ cout<<"Wrapper1 copy ctor\n"; }
};
template <typename W> test(){
  //W tmp;
  //W tmp2 = move(tmp);
  vector<W> vec;
//  vec.push_back(move(W()) );
}
void testMove(Wrapper1 && rhs){
  cout<<"testMove\n";
  Wrapper1 local=move(rhs);
}
int main(){
  Wrapper1 w;
  testMove(move(w));
#ifdef aaaa
  test<Wrapper1>();
  test<Wrapper2>();
  testFactory<Wrapper3>();
  testFactory<Wrapper4>();
#endif
}

struct Wrapper2{
  shared_ptr<Payload> sp=make_shared<Payload>();
  Wrapper2(){cout<<"Wrapper2 ctor\n"; }
  Wrappper2(Wrapper2 &&) = delete;
  Wrapper2(Wrapper2 const & rhs): sp(rhs.sp){
	cout<<"Wrapper2 copy ctor\n"; 
  }
};
class Wrapper3{
  shared_ptr<Payload> sp=make_shared<Payload>();
  Wrapper3(){cout<<"Wrapper--3 ctor\n"; }
public:
  Wrapper3(Wrapper3 const & rhs): sp(rhs.sp){
	cout<<"Wrapper--3 copy ctor\n"; 
  }
  static Wrapper3 make(){return Wrapper3(); }
};
class Wrapper4{
  shared_ptr<Payload> sp=make_shared<Payload>();
  Wrapper4(){cout<<"Wrapper--4 ctor\n"; }
public:
  Wrapper4(Wrapper4 const & rhs): sp(rhs.sp){
	cout<<"Wrapper--4 copy ctor\n"; 
  }
  static Wrapper4 make(){
    static Wrapper4 inst;
	return inst; 
  }
};
template <typename W> testFactory(){
  vector<W> vec;
  vec.push_back(W::make() );
}
