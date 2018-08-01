/*
todo: simplify before creating the iterative solution
todo: can use a list? queue can't take in a range
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
#include <list>
#include <deque>
#include <set>
#include <assert.h>
#define outer std::list
size_t calls=0, combos=0;

template<typename T> void dumpPool(std::deque<T> const & p, std::string const & s=""){
  std::cout<<"------------ "<<s<<" ------------ size = "<<p.size()<<": ";
  for(int i=0; i<p.size(); ++i) std::cout<<p[i];
  std::cout<<std::endl;
}
template<typename T> int show(outer<std::deque<T> > const & p){
  std::stringstream ss;
  std::string last = "";
  for(auto const & v : p){
    if (v.size() ){
      for(int j=0; j<v.size(); ++j) ss<<v[j];
    }else ss<<"<empty>";
    assert(last < ss.str());
    std::cout<<ss.str()<<std::endl; //one abbr
    last = ss.str();
    ss.str("");
  }
  std::cout<<"--- abbr count = "<<p.size()<<"\n";
}

// Below is the actual algo .. rather short
template<typename T> outer<std::deque<T> > const & //void return type is enough for this algo
recurs(std::deque<T> const & pool, bool isFresh=false){
  ++calls;
  static outer<std::deque<T> > global_coll;
  if (isFresh) global_coll.clear();
  dumpPool(pool, "entering");
  if (pool.size() == 1){ //recursion exit condition
    global_coll.push_back(std::deque<T>());
    global_coll.push_back(pool);
    show(global_coll);
    return global_coll;
  }
  recurs( std::deque<T>(pool.begin()+1,pool.end()) );  //the new pool passed in is shorter

  outer<std::deque<T> > tmpColl;
  for(auto abbr //clone each item in global_coll
       : global_coll){
    abbr.push_front (pool[0]); //prepend 1st char in pool to make a new abbr
    tmpColl.push_back(abbr);
  }// tmpColl to be merged into global_coll
  global_coll.splice(++(global_coll.begin()), tmpColl);

#ifdef DEBUG
  assert(global_coll.front().size() == 0 && "1st abbreviation in the collection must be the empty abbreviation");
  static int lastSize= -1 ;
  size_t newSize = global_coll.size();
  assert(lastSize < 0 || lastSize*2 == newSize && "global_coll.size() should double after the insert()");
  lastSize = newSize;
  show(global_coll);
#endif
  return global_coll;
}
auto const & generateAsc(std::string const & s){
  std::deque<char> v(s.begin(), s.end());
  auto const & ret = recurs(v, true);
  return ret;
}
/* abbreviation or subsequence generator, to be included in ..
*/