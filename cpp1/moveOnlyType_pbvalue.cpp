#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct MoveOnlyStr{ //a string class that robs its sister instance
#ifdef aaaa
  MoveOnlyStr& operator=(MoveOnlyStr && sister){
    _nonref = move(sister._nonref);
    _ptr = sister._ptr; 
    sister._ptr=NULL;
    cout<<this<<" <-- "<<*_ptr<<" repopulated in MOVE-assignment\n";
    return *this;
  }
#endif
  MoveOnlyStr(MoveOnlyStr && sister){
    _nonref = move(sister._nonref); /*nonref variable needs std::move()
so we can use the move-assignment of std::string*/
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
      os<<"[ a MoveOnlyStr instance containing a null ptr and a nonref ="
	  <<me._nonref<<"]";
    }
    return os;
  }
private:  
  string * _ptr;
  string _nonref;
};
MoveOnlyStr factory(string s){ //RVO probably constructs the object on caller's stack frame 
  MoveOnlyStr ret(s);
  cout<<&ret<<" <- address of factory return object\n";
  cout<<"temp ret object created, now returning by value\n";
  return ret;
}
void testFactory(){
  MoveOnlyStr a = factory(string("arg"));
  cout<<&a<<" <- address of factory output object\n";
}/////////////
void receive(MoveOnlyStr clonedArg){
  cout<<&clonedArg<<" <- address of argument object passed in by value\n";
}
void testPassInByValue(){
  MoveOnlyStr uniquePtrimitator("input");
  cout<<&uniquePtrimitator<<" <- address of original object before passing by value\n";
//receive(uniquePtrimitator); //nonref needs copy-ctor. Won't compile
  receive(move(uniquePtrimitator)); 
  cout<<uniquePtrimitator<<endl;
}
int main(){
  testPassInByValue();
}
/*Goal is to test how a move-only type (like st::mutex or unique_ptr) is passed by value

Let's return this object from factory, save it in container...
*/