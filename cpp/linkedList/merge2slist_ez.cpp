/*
showcase: use ptr to indirectly advance two iterators in a single loop
showcase: declare multiple iterator variables in for-loop header
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
list<item> merge(){
  li1.sort();  li2.sort();// should be sorted already.
  list<item> ret;
  for (auto i1=li1.cbegin(), i2=li2.cbegin();;){
    auto i = &(*i1 < *i2? i1: i2);
    assert(ret.empty() || ret.back() <= **i);
    ret.push_back(**i);
    ++*i; //indirectly advance one of the iterators
    if (i1 == li1.end()){
      for (; i2 != li2.end(); ++i2)     ret.push_back(*i2);
      break;
    }
    if (i2 == li2.end()){
      for (; i1 != li1.end(); ++i1)     ret.push_back(*i1);
      break;
    }
  }
  assert(ret.size() == li1.size() + li2.size());
  return ret;
}
int main(){
  cout<<merge();
}
/*Req: given 2 pre-sorted slists, merge-sort them to a new slist
*/
