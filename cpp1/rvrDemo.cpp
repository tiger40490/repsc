#include <iostream>
#include <vector>
using namespace std;

struct mystring{
  mystring(string const & s){
    _ptr = new string(s);
    _nonref = s;
    cout<<*_ptr<<" populated in no arg ctor\n";
  }
  mystring(mystring const & s){
    _ptr = new string(*s._ptr);
    _nonref = s._nonref;
    cout<<*_ptr<<" populated in copy-ctor\n";
  }
  mystring(mystring && s){
    _nonref = move(s._nonref); //nonref field needs std::move()
    _ptr = s._ptr; // ptr field needs not std::move()
    s._ptr=nullptr;
    cout<<*_ptr<<" populated in move-ctor\n";
  }
  ~mystring(){delete _ptr;}
  friend ostream & operator<<(ostream & os, mystring const & me){
    if (me._ptr){
      os<<*me._ptr<<"/"<<me._nonref;
    }else{
      os<<"a mystring instance containing a null ptr and nonref = "<<me._nonref;
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
  mystring s("a1");
  mystring & lvr=s;
  vec.push_back(move(lvr));
  
  mystring s2("b2");
  vec.push_back(s2); //regular copy ctor
  vec.push_back(move(s2));
  
  vec.emplace_back("c3"); //no move-ctor used
  for(int i=0; i<vec.size(); ++i)
    cout<<i<<": "<<vec[i]<<"  ";
  cout<<endl;
  cout<<s<<" ... is original string, now vacant.\n";
}
