#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


template<typename K, typename V> std::ostream & operator<<(std::ostream & os, std::pair<K,V> const & p){
   os<<p.first<<":"<<p.second;
   return os;
}

class NoCtor{
public: // the fields must be public !
  float f;
  pair<int, string> p;
  vector<int> v;
  void dump(){
    cout<<f<<"=theFloat, theVector.size()="<<v.size()<<", pair="<<p<<endl;  
  }
};

int main(){
  // note the initialization with nothing but braces
  NoCtor full{3.2, {5, "dummyStr"}, {3,2,8}};
  full.dump();
  
  // note the initialization using qq[=]
  NoCtor barebones={};
  barebones.dump();
  
  NoCtor firstPart{5.6};
  firstPart.dump();
}
/* In ValueObjects of my coding tests, I often want to make do without defining/updating ctor. 
The more code there is in ctor, the more chances of mistakes.
*/