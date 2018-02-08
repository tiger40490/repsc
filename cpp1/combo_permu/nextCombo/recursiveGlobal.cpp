//This recursive version suffers from stack overflow but
//it's able to print out combinations in ascending order and
//maintains the relative positions between any 2 items
//
//This version reduces vector cloning by growing/shrinking
//global objects but with higher complexity
//
//However, global variables actually simplify the logic!
//
// 51 calls to recursive func
#include <iostream>
#include <sstream>
#include <deque>
#include <iomanip> //setw
#include <algorithm>  //sort
#include <assert.h>
//#define DEBUG
using namespace std;
size_t calls=0, combos=0;
size_t const C=3; //how many in each combination
string tmp = "abcde";
deque<char> pool(tmp.begin(), tmp.end());
deque<char> prefix;

template<typename T> void dumpDeque(deque<T> const & p, string const & headline){
  cout<<"-- "<<headline<<" -- size = "<<p.size()<<endl;
  for(int i=0; i<p.size(); ++i) cout<<setw(5)<<p[i];
  cout<<endl;
}
template<typename T> int showCombo(deque<T> const * p){
  ++ combos;
  stringstream ss;
  for(int i=0; i<p->size(); ++i) ss<<setw(5)<<(*p)[i];
  static string last;
  string combo=ss.str();
  cout<<"combo: "<<combo<<endl;
  assert(last <= combo && "should be ascending");
  last = combo;
}

template<typename T> int recurs(){
  ++calls;
#ifdef DEBUG
  cout<<"-------------\nentering "; dumpDeque(prefix, "prefix"); dumpDeque(pool, "pool");
#endif
  if (prefix.size() == C) return showCombo(&prefix);
  if (pool.empty()) return 0;
  T poolhead = pool.front(); pool.pop_front();

  prefix.push_back(poolhead); //add poolhead to prefix

  //this 1st recursive function call starts a rather deep call stack and prints
  //all combinations with the given (new longer) prefix
  recurs<T>();//use the longer prefix and the shorter pool
  prefix.pop_back();//restore prefix
  recurs<T>();
  pool.push_front(poolhead); //restore pool, needed by the 2nd call in the parent stack
#ifdef DEBUG
  cout<<"^^^^^^ restored before returning "; dumpDeque(prefix, "prefix"); dumpDeque(pool, "pool");
#endif
}

int main() {
  assert(C <= pool.size());
  recurs<char>();
  cout<<calls<<"  calls to the recursive function to generate "<<combos<<endl;
}
