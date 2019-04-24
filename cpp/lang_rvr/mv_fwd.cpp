#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Badstr{ //a string class that robs its sister instance
  Badstr& operator=(Badstr && sister){
  //this function doesn't clean up the existing this->_nonref and this->ptr
    _nonref = move(sister._nonref);
    _ptr = sister._ptr; 
    sister._ptr=NULL;
    cout<<this<<" <-- "<<*_ptr<<" repopulated in MOVE-assignment\n";
    return *this;
  }
  Badstr(Badstr && sister){
    _nonref = move(sister._nonref); /*nonref variable needs std::move()
so we can use the move-assignment of std::string*/
    _ptr = sister._ptr; // ptr field needs no std::move()
    sister._ptr=nullptr;
    cout<<this<<" <-- "<<*_ptr<<" populated in MOVE-ctor\n";
  }
  Badstr(string const & s){
    _ptr = new string(s);
    _nonref = s;
    cout<<this<<" <-- "<<*_ptr<<" populated in converter-ctor\n";
  }
  Badstr(Badstr const & s){
    _ptr = new string(*s._ptr);
    _nonref = s._nonref;
    cout<<this<<" <-- "<<*_ptr<<" populated in copy-ctor\n";
  }
  ~Badstr(){delete _ptr;}
  friend ostream & operator<<(ostream & os, Badstr const & me){
    if (me._ptr){
      os<<*me._ptr<<"/"<<me._nonref;
    }else{
      os<<"[ a Badstr instance containing a null ptr and a nonref ="
	  <<me._nonref<<"]";
    }
    return os;
  }
private:  
  string * _ptr;
  string _nonref;
}; //class

void pbvalFunc(Badstr clone){
  cout<<&clone<<" In pbvalFunc(), the arg object address would be same as the orig object in caller if the orig is an unnamed temporary!"<<endl;
}
void testPbValue(){
  pbvalFunc(Badstr("temp3")); //no move no copy... Instead, the Badstr instance is created directly in the callee's stack, similar to RVO. 
  // * Compiler optimizes away the temporary object completely. More efficient than Scott Meyers and Shanyou said.
  
  //Above was passing an UNNAMED temporary into pbvalFunc(). 
  //Below we pass a named object into pbvalFunc().
  
  Badstr nonref("nonref");
  pbvalFunc(nonref); //invokes regular copy-ctor. No optimizer magic :(
  cout<<"^^^^^    done with pbvalue test    ^^^^^\n\n";  
}
void testAssignment(){
  Badstr me("var1");
  Badstr sister("sister");
  me.operator=(move(sister));
  //me=move(sister); 
  cout<<"^^^^^    done with testAssignment()    ^^^^^\n\n";
}
void testEmplace(){
  cout<<"Now declaring vector<Badstr>...\n";
  vector<Badstr> vec;
  vec.reserve(5);
  Badstr s0("c++03");
  vec.push_back(s0); //c++03 style copy ctor

  Badstr s1("L_ValueRef");
  Badstr & lValueRef=s1;
  vec.push_back(move(lValueRef));
  
  Badstr s2("nonref");
  vec.push_back(move(s2));
  
  vec.push_back(Badstr("tempObj")); //no std::move() required on a temp object. move-ctor is selected automatically
  
  vec.emplace_back("fwd"); //Most efficient. no temp no move-ctor
  for(int i=0; i<vec.size(); ++i)
    cout<<i<<" @ "<<&vec[i]<<" : "<<vec[i]<<"\n";
  cout<<endl;
  cout<<s1<<" ... is original string, now vacant.\n";
  cout<<"^^^^^    done with testEmplace()    ^^^^^\n\n";  
}
////////////////////////////////////
struct Trade{
  Trade(Badstr && s):display(move(s)) /*without move(), s is passed to 
  Badstr ctor as LLLLvr !*/ {
    cout<<"Trade ctor received a RRRRvr "<<display<<endl;
  }
  Trade(Badstr & s):display(s) /*Trade class developer should Not
move(s) here because the object behind s is not a temporary. Std::move 
would surprise whoever using this Trade ctor. Given it is non-const 
We can modify but not rob it. */ {
    cout<<"Trade ctor received a  LLLLvr "<<display<<endl;
  }
  Badstr display;
};
template <typename A> shared_ptr<Trade> factory(A && s){
  // A is a universal reference, not a rvr !
  return make_shared<Trade>(forward<A>(s));

  //The version below is broken  as Trade ctor would always get Lvr even if s is temp
  //return make_shared<Trade>(s);
}
void test_fwd(){
  auto shp = factory(Badstr("temp-Badstr"));
  cout<<shp->display<<" = in the shared_ptr returned from factory\n\n";
  
  Badstr nonref1("nonref1-Badstr");
  shp = factory(move(nonref1)); 
  cout<<shp->display<<" = in the shared_ptr from factory\n\n";

  Badstr nonref2("nonref2-Badstr");
  shp = factory(nonref2); /*won't move. Note: factory<Badstr>(lvr) won't
compile as it disables type deduction and remove universsal reference*/
  cout<<"^^^^^    done with test_fwd()    ^^^^^\n\n";  
}
int main(){
  testPbValue();
  testAssignment();
  testEmplace();
  test_fwd();
}
