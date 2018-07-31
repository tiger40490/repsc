/*todo: don't use namespace std
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
#include <vector>
#include <deque>
#include <set>
#include <assert.h>
using namespace std;
size_t calls=0, combos=0;

template<typename T> void dump1abbr(deque<T> const & p, string const & s=""){
  cout<<"------------ "<<s<<" ------------ size = "<<p.size()<<endl;
  for(int i=0; i<p.size(); ++i) cout<<p[i];
  cout<<endl;
}
template<typename T> int show(deque<deque<T> > const & p){
  stringstream ss;
  for(int i=0; i<p.size(); ++i){
    deque<T> const & v = p[i];
    if (v.size() ){
      for(int j=0; j<v.size(); ++j) ss<<v[j];
    }else ss<<"<empty>";
    ss<<endl;
  }
  cout<<"abbr count = "<<p.size()<<endl<<ss.str()<<endl;
}

// Below is the actual algo .. rather short
template<typename T> deque<deque<T> > const & //void return type is enough for this algo
recurs(deque<T> const & pool){
  ++calls;
  static deque<deque<T> > global_coll;
//  dump1abbr(pool, "entering");
  if (pool.size() == 1){ //exit condition
    global_coll.push_back(deque<T>());
    global_coll.push_back(pool);
    return global_coll;
  }
  recurs( deque<T>(pool.begin()+1,pool.end()) );  //the new pool passed in is shorter

  deque<deque<T> > tmpColl;
  for(int i=0; i<global_coll.size(); ++i){
    deque<T> abbr = global_coll[i];
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
deque<deque<char> > const & generate(std::string const & s){
  deque<char> v(s.begin(), s.end());
  auto const & ret = recurs(v);
  return ret;
}
/* abbreviation or subsequence generator, to be included in ..
*/