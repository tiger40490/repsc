/*a SCB onsite question shared by Ashish

Passing a temp object into push_back() invokes the rvr version of push_back. If the object supports mv-ctor then the mv-ctor get picked, otherwise the copy-ctor gets picked.

That's the conclusion from this lengthy experiment.

showcase c++11 field initializer on field declaration, outside the constructor ... which probably gets executed before move-ctor !
*/
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
using namespace std;
struct Payload{
  static size_t cnt;
  Payload(){++cnt; cout<<"Payload ctor\n"; }
};
struct Wrapper1{
  static size_t mvCnt, cpCnt;
  shared_ptr<Payload> sp;
  double id;
  Wrapper1(double i=11.1): sp(make_shared<Payload>() ) 
  {id=i; cout<<i<<" Wrapper1 ctor\n"; }  
  
  Wrapper1(Wrapper1 && rhs): id(rhs.id) {
    swap(this->sp, rhs.sp); //not sure
    cout<<id<<" Wrapper1 move ctor done "<<this->sp.get()<<"=this->sp , rhs.sp="<<rhs.sp<<endl; 
    ++mvCnt;
  }
  
  Wrapper1(Wrapper1 const & rhs): id(rhs.id), sp(rhs.sp){ 
    cout<<id<<" Wrapper1 copy ctor done\n"; 
    ++cpCnt;
  }
  static Wrapper1 make(){return Wrapper1(11.777); } //RVO should kick in
}; 
struct Wrapper2{ 
//mv-ctor deleted, so each mv-ctor call is now a cp-ctor call, even though push_back() receives a temp object
  static size_t cpCnt;
  shared_ptr<Payload> sp;
  double id;
  Wrapper2(double i=22.2): sp(make_shared<Payload>() ) 
  {id=i; cout<<i<<" Wrapper2 ctor\n"; }  
  Wrappper2(Wrapper2 &&) = delete;
  Wrapper2(Wrapper2 const & rhs): id(rhs.id), sp(rhs.sp){ 
    cout<<id<<" Wrapper2 copy ctor done\n"; 
    ++cpCnt;
  }
  static Wrapper2 make(){return Wrapper2(22.888); }
};
size_t Payload::cnt=0;
size_t Wrapper1::mvCnt=0;
size_t Wrapper1::cpCnt=0;
size_t Wrapper2::cpCnt=0;
template <typename W> test(){
  vector<W> vec;
  vec.reserve(88); //without this, initial capacity is one
  vec.push_back( W() );//favors move-ctor due to naturally-occurring rval object
  cout<<"now calling make()..\n";
  vec.push_back( W::make() ); //also favors move-ctor
}
int main(){
  test<Wrapper1>();
  assert(Wrapper1::mvCnt == 2 && Wrapper1::cpCnt == 0);
  cout<<"---------- Wrapper2 tests ---------\n";
  test<Wrapper2>();
  //cout<<to_string(Wrapper2::cpCnt) + " is the actual value\n";
  assert(Wrapper2::cpCnt == 2); // 2 copies around the factory
}
