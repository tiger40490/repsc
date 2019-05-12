/*
showcase: use ptr to indirectly advance two iterators in a single loop
showcase: declare multiple iterator variables in for-loop header
showcase: typedef for readability
showcase: auto const & as a simpler variable type
*/
#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm> //is_sorted
#include <assert.h>
using namespace std;
typedef int item;
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, list<T> const & c){
   for(auto const & it: c){ os<<setw(min_width)<<it<<" "; }
   os<<endl;
   return os;
}
list<item> _merge(list<item> & liA, list<item> & liB){
  assert(is_sorted(liA.begin(), liA.end()));
  assert(is_sorted(liB.begin(), liB.end()));
  list<item> ret;
  for (auto iA=liA.cbegin(), iB=liB.cbegin();;){
    auto const& i = &(*iA < *iB? iA: iB);
    assert(ret.empty() || ret.back() <= **i);
    ret.push_back(**i);
    ++*i; //indirectly advance one of the iterators
    
    if (iA == liA.end()){
      ret.insert(iA, iB, liB.cend());
      return ret; //RVO should take place. No move() please
    }
    if (iB == liB.end()){
      for (; iA != liA.end(); ++iA)ret.push_back(*iA); //for-loop is easier to remember
      return ret; //RVO should take place. No move() please
    }
  }
}
list<item> merge(list<item> & liA, list<item> & liB){
  auto const & ret = _merge(liA, liB);
  assert(ret.size() == liA.size() + liB.size());
  assert(is_sorted(ret.begin(), ret.end()));
  return ret; //RVO should take place. No move() please
}
int main(){
  list<item> liB={6,12,16,33,46,48,48,68,73,75,76,77,78};
  list<item> liA={5,11,31,34,38,50,61,66,71,74};
  cout<<merge(liA, liB);
}
/*Req: given 2 pre-sorted slists, merge-sort them to a new slist
*/
