//This recursive version suffers from stack overflow
//but it's able to print out combinations in ascending order and
//maintains the relative positions between any 2 items
//
#include <iostream>
#include <vector>
#include <iomanip> //setw
#include <algorithm>  //sort
#include <assert.h>
using namespace std;
size_t calls=0, combos=0;
size_t const C=3; //how many in each combination
vector<char> const emptyV;

template<typename T> void dump(vector<T> const & p, string const & s){
  cout<<"------------ "<<s<<" ------------ size = "<<p.size()<<endl;
  for(int i=0; i<p.size(); ++i) cout<<setw(5)<<p[i];
  cout<<endl;
}
template<typename T> int show(vector<T> const * p, vector<T> const * v = NULL){
  ++ combos;
  cout<<"combo: ";
  for(int i=0; i<p->size(); ++i) cout<<setw(5)<<(*p)[i];
  if (v){
    cout<<",";
    for(int i=0; i<v->size(); ++i) cout<<setw(5)<<(*v)[i];
  }
  cout<<endl;
}

template<typename T> int recurs(vector<T> const & prefix, vector<T> const & pool){// size_t const suffix ){
  ++calls;
//  cout<<"entering"<<endl; dump(prefix, "prefix"); dump(pool, "pool");
  if (prefix.size()            == C) return show(&prefix);
  if (prefix.size()+pool.size()== C) return show(&prefix, &pool);
  //create modified clones
  vector<T> newPrefix(prefix); newPrefix.push_back(pool[0]);
  vector<T> const newPool(pool.begin()+1, pool.end());
  recurs(newPrefix, newPool);
  recurs(prefix, newPool);
}

int main() {
  string tmp = "abcde";
  vector<char> v(tmp.begin(), tmp.end());
  assert(C <= v.size());
  recurs(emptyV, v);
  cout<<calls<<"  calls to the recursive funcion to generate "<<combos<<endl;
}
