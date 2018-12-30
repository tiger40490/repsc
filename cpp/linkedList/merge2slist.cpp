/*
showcase: typedef for readability
*/
#include <iostream>
#include <iomanip>
#include <list>
#include <assert.h>
using namespace std;
typedef int item;
list<item> li2={6,12,16,33,46,48,48,68,73,75,76,77,78};
list<item> li1={5,11,31,34,38,50,61,66,71,74};
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, list<T> const & c){
   for(auto const & it: c){ os<<setw(min_width)<<it<<" "; }
   os<<endl;
   return os;
}
list<item> process(){
  list<item> ret;
  auto i1=li1.cbegin(), i2=li2.cbegin();
  for (;;){
    auto i = &i2;
    if (*i1 < *i2){
      i = &i1;
    }
    assert(ret.back()<=**i);
    ret.push_back(**i);
    //cout<<(**i)<<" ";
    ++*i;
    //if ( i == i1){
    if (*i == li1.end()){
      for (i=&i2; *i != li2.end(); ++*i)     ret.push_back(**i);
      return ret;
    }
    if (*i == li2.end()){
      for (i=&i1; *i != li1.end(); ++*i)     ret.push_back(**i);
      return ret;
    }
  }
}
int main(){
  cout<<process();
}
/*
*/
