#include <iostream>
#include <vector>
using namespace std;

struct mystring{
  mystring(string const & s){
    _ptr = new string(s);
	cout<<*_ptr<<" populated in no arg ctor\n";
  }
  mystring(mystring const & s){
    _ptr = new string(*s._ptr);
	cout<<*_ptr<<" populated in copy-ctor\n";
  }
  mystring(mystring && s){
    _ptr = s._ptr;
	s._ptr=nullptr;
	cout<<*_ptr<<" populated in move-ctor\n";
  }
  ~mystring(){delete _ptr;}
  friend ostream & operator<<(ostream & os, mystring const & me){
    if (me._ptr){
	  os<<*me._ptr;
	}else{
	  os<<"a mystring instance containing a null ptr";
	}
	return os;
  }
private:  
  string * _ptr;
};
int main(){
  vector<mystring> vec;
  vec.reserve(5);
  mystring s("a1");
  mystring & lvr=s;
  vec.push_back(move(lvr));
  
  mystring s2("b2");
  vec.push_back(s2);
  vec.push_back(move(s2));
  vec.emplace_back("c3"); //no move-ctor used
  for(int i=0; i<vec.size(); ++i)
    cout<<i<<": "<<vec[i]<<"  ";
  cout<<endl;
  cout<<s<<" ... is original string, now vacant.\n";
}