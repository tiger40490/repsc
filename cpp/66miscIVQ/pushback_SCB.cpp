/*a SCB onsite question shared by Ashish

showcase field initializer on field declaration, outside the constructor ... Not possible before c++11

Q: why is push_back() always calling the copy ctor?
*/
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
using namespace std;
long choice=0;
struct Payload{
  Payload(){cout<<"Payload ctor\n"; }
};
struct Wrapper1{
  shared_ptr<Payload> sp;
  Wrapper1(): sp(make_shared<Payload>()) {cout<<"Wrapper1 ctor\n"; }  
  Wrapper1(Wrapper1 && rhs){
	swap(this->sp, rhs.sp); //not sure
	cout<<"Wrapper1 move ctor done "<<this->sp.get()<<"=this->sp , rhs.sp="<<rhs.sp<<endl; 
    choice = 1000+'m';
  }
  Wrapper1(Wrapper1 const & rhs)
  : sp(rhs.sp){ cout<<"Wrapper1 copy ctor\n"; }
};
struct Wrapper2{ //mv-ctor deleted
  shared_ptr<Payload> sp;
  Wrapper2(): sp(make_shared<Payload>()) {cout<<"Wrapper2 ctor\n"; }  
  Wrappper2(Wrapper2 &&) = delete;
  Wrapper2(Wrapper2 const & rhs)
  : sp(rhs.sp){ cout<<"Wrapper2 copy ctor\n"; choice = 2000+'c';}
};
template <typename W> test(){
  vector<W> vec;
  vec.push_back( W() );//favors move ctor due to naturally-occurring rval object
}
int main(){
  test<Wrapper1>();
  assert(choice==1000+'m');
  test<Wrapper2>();
  assert(choice==2000+'c');
#ifdef aaaa
  testFactory<Wrapper3>();
  testFactory<Wrapper4>();
#endif
}

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
