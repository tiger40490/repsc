#include <iostream>
#include <vector>
using namespace std;

struct mystring{
  mystring(string const & s){
    _ptr = new string(s);
    _nonref = s;
    cout<<this<<" <-- "<<*_ptr<<" populated in converter-ctor\n";
  }
  mystring(mystring const & s){
    _ptr = new string(*s._ptr);
    _nonref = s._nonref;
    cout<<this<<" <-- "<<*_ptr<<" populated in copy-ctor\n";
  }
  mystring(mystring && s){
    _nonref = move(s._nonref); //nonref field needs std::move()
    _ptr = s._ptr; // ptr field needs not std::move()
    s._ptr=nullptr;
    cout<<this<<" <-- "<<*_ptr<<" populated in move-ctor\n";
  }
  ~mystring(){delete _ptr;}
  friend ostream & operator<<(ostream & os, mystring const & me){
    if (me._ptr){
      os<<*me._ptr<<"/"<<me._nonref;
    }else{
      os<<"[ a mystring instance containing a null ptr and nonref = "<<me._nonref<<" ]";
    }
    return os;
  }
private:  
  string * _ptr;
  string _nonref;
};
int main(){
  vector<mystring> vec;
  vec.reserve(5);
  mystring s0("c++03");
  vec.push_back(s0); //c++03 style copy ctor

  mystring s1("L_ValueRef");
  mystring & lValueRef=s1;
  vec.push_back(move(lValueRef));
  
  mystring s2("nonref");
  vec.push_back(move(s2));
  
  vec.push_back(mystring("tempObj")); //no std::move() required on a temp object. move-ctor is selected automatically
  
  vec.emplace_back("fwd"); //Most efficient. no temp no move-ctor
  for(int i=0; i<vec.size(); ++i)
    cout<<i<<" @ "<<&vec[i]<<" : "<<vec[i]<<"\n";
  cout<<endl;
  cout<<s1<<" ... is original string, now vacant.\n";
}
