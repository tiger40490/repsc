/*
todo: simplify before creating the iterative solution
*/
//As a Recursive solution , this one suffer from stack overflow
//but it's able to print out all abbreviations in ascending order,
//where 'ascending' is defined on the basis that within the
//original word, a char
//has lower value than any char on its right. This is more clear
//when the word itself is a sorted string, but actually it's
//not needed.

//This algo uses a global collection, rather than passing a collection
//between the recursive calls. This effectively simplifies the design.
//Any variable passed into a recursive call is additional state on the stack
//and makes the logic harder to reason about.

//If any char is not unique, the only solution I know relies on an external
//lookup device.
#include <iostream>
#include <sstream>
#include <deque>
#include <set>
#include <assert.h>
size_t calls=0, combos=0;

template<typename T> void dump1abbr(std::deque<T> const & p, std::string const & s=""){
  std::cout<<"------------ "<<s<<" ------------ size = "<<p.size()<<std::endl;
  for(int i=0; i<p.size(); ++i) std::cout<<p[i];
  std::cout<<std::endl;
}
template<typename T> int show(std::deque<std::deque<T> > const & p){
  std::stringstream ss;
  for(int i=0; i<p.size(); ++i){
    std::deque<T> const & v = p[i];
    if (v.size() ){
      for(int j=0; j<v.size(); ++j) ss<<v[j];
    }else ss<<"<empty>";
    ss<<std::endl;
  }
  std::cout<<"abbr count = "<<p.size()<<std::endl<<ss.str()<<std::endl;
}

// Below is the actual algo .. rather short
template<typename T> std::deque<std::deque<T> > const & //void return type is enough for this algo
recurs(std::deque<T> const & pool, bool isFresh=false){
  ++calls;
  static std::deque<std::deque<T> > global_coll;
  if (isFresh) global_coll.clear();
//  dump1abbr(pool, "entering");
  if (pool.size() == 1){ //exit condition
    global_coll.push_back(std::deque<T>());
    global_coll.push_back(pool);
    return global_coll;
  }
  recurs( std::deque<T>(pool.begin()+1,pool.end()) );  //the new pool passed in is shorter

  std::deque<std::deque<T> > tmpColl;
  for(int i=0; i<global_coll.size(); ++i){
    std::deque<T> abbr = global_coll[i];
    abbr.push_front (pool[0]); //prepend 1st char in pool to make a new abbr
    tmpColl.push_back(abbr);
  }// tmpColl to be merged into global_coll
  global_coll.insert(global_coll.begin()+1, tmpColl.begin(), tmpColl.end());

#ifdef DEBUG
  assert(global_coll[0].size() == 0 && "1st abbreviation in the collection must be the empty abbreviation");
  static int lastSize= -1 ;
  size_t newSize = global_coll.size();
  assert(lastSize < 0 || lastSize*2 == newSize && "global_coll.size() should double after the insert()");
  lastSize = newSize;
  show(global_coll);
#endif
  return global_coll;
}
std::deque<std::deque<char> > const & generateAsc(std::string const & s){
  std::deque<char> v(s.begin(), s.end());
  auto const & ret = recurs(v, true);
  return ret;
}
/* abbreviation or subsequence generator, to be included in ..
*/