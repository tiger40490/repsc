//This recursive version suffers from stack overflow
//but it's able to print out combinations in ascending order and
//maintains the relative positions between any 2 items
//
//This version reduces vector cloning by growing/shrinking the deques
//but with higher complexity
//
// 19 calls to recusive func
#include <iostream>
#include <sstream>
#include <deque>
#include <iomanip> //setw
#include <algorithm>  //sort
#include <assert.h>
using namespace std;
size_t calls=0, combos=0;
size_t const C=3; //how many in each combination
deque<char> emptyV;
deque<char> prefix, pool;

template<typename T> void dumpDeque(deque<T> const & p, string const & headline){
  cout<<"-- "<<headline<<" -- size = "<<p.size()<<endl;
  for(int i=0; i<p.size(); ++i) cout<<setw(5)<<p[i];
  cout<<endl;
}
template<typename T> int showCombo(deque<T> const * p, deque<T> const * v = NULL){
  ++ combos;
  stringstream ss;
  for(int i=0; i<p->size(); ++i) ss<<setw(5)<<(*p)[i];
  if (v){
    //cout<<",";
    for(int i=0; i<v->size(); ++i) ss<<setw(5)<<(*v)[i];
  }
  static string last;
  string combo=ss.str();
  cout<<"combo: "<<combo<<endl;
  assert(last <= combo);
  last = combo;
}

template<typename T>
int recurs(){//deque<T> & prefix, deque<T> & pool){// size_t const suffix ){
  ++calls;
  //cout<<"-------------\nentering"<<endl; dumpDeque(prefix, "prefix"); dumpDeque(pool, "pool");
  if (prefix.size()            == C) return showCombo(&prefix);
  if (prefix.size()+pool.size()== C) return showCombo(&prefix, &pool); // no other choice

  assert(!pool.empty());
  T poolhead = pool.front(); pool.pop_front();

  prefix.push_back(poolhead); //add poolhead to prefix

  //this function call starts a rather deep call stack and prints
  //all combinations with the given (new longer) prefix
  recurs<T>();//prefix, pool);//use the longer prefix and the shorter pool
  prefix.pop_back();//restore prefix
  recurs<T>();//prefix, pool);
  pool.push_front(poolhead); //restore pool, needed by the 2nd call in the parent stack
}

int main() {
  string tmp = "abcde";
  deque<char> v(tmp.begin(), tmp.end());
  assert(C <= v.size());
  prefix = emptyV;
  pool = v;
  recurs<char>();//emptyV, v);
  cout<<calls<<"  calls to the recursive funcion to generate "<<combos<<endl;
}
