#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct MoveOnlyStr{ //a string class that robs its sister instance
#ifdef commentedOut123
  MoveOnlyStr& operator=(MoveOnlyStr && sister){
    _nonref = move(sister._nonref); //std::string rvr-assignment i.e. mv-assign
    _ptr = sister._ptr; 
    sister._ptr=NULL;
    cout<<this<<" <-- "<<*_ptr<<" repopulated in MOVE-assignment\n";
    return *this;
  }
#endif
  MoveOnlyStr(MoveOnlyStr && sister){
    _nonref = move(sister._nonref); /*nonref variable needs std::move()
so we can use the move-ctor of std::string*/
    _ptr = sister._ptr; // ptr field needs no std::move()
    sister._ptr=nullptr;
    cout<<this<<" <-- "<<*_ptr<<" populated in MOVE-ctor\n";
  }
  MoveOnlyStr(string const & s){
    _ptr = new string(s);
    _nonref = s;
    cout<<this<<" <-- "<<*_ptr<<" populated in converter-ctor\n";
  }
  MoveOnlyStr(MoveOnlyStr const & s) = delete;
  ~MoveOnlyStr(){delete _ptr;}
  friend ostream & operator<<(ostream & os, MoveOnlyStr const & me){
    if (me._ptr){
      os<<*me._ptr<<"/"<<me._nonref;
    }else{
      os<<"[ a MoveOnlyStr instance containing a null ptr, and a nonref equal to "
	  <<me._nonref<<"]";
    }
    return os;
  }
private:  //two unrelated data members
  string * _ptr;
  string _nonref;
};
MoveOnlyStr factory(string s){ //RVO constructs the object on caller's stack frame without move-ctor
  MoveOnlyStr ret(s);
  cout<<&ret<<" <- address of factory return object\n";
  cout<<"temp ret object created, now returning by value\n";
  return ret;
}
void testFactory(){
  MoveOnlyStr a = factory(string("arg"));
  cout<<&a<<" <- address of factory output object as seen in caller\n";
}/////////////
void receive(MoveOnlyStr clonedArg){
  cout<<&clonedArg<<" <- address of argument object passed in by value\n";
}
void testPassInByValue(){ //explicit move() needed
  MoveOnlyStr uniquePtrimitator("input");
  cout<<&uniquePtrimitator<<" <- address of original object before passing by value\n";
  receive(move(uniquePtrimitator)); 
//receive(uniquePtrimitator); //nonref needs copy-ctor. Won't compile
  cout<<uniquePtrimitator<<endl;
}
void testContainer(){ //explicit move() needed
  MoveOnlyStr bb("bb");
  vector<MoveOnlyStr> arr;
  arr.push_back(move(bb));
//arr.push_back(bb); //nonref needs copy-ctor. Won't compile
  cout<<bb<<endl;
}
int main(){
  testFactory();
//testContainer();
}
/*Goal is to test how a move-only type (like st::mutex or unique_ptr) is passed by Value
*/