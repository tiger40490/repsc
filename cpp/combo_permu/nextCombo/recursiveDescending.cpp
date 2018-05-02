//This recursive version suffers from stack overflow
//but it's able to print out combinations in Descending order and
//maintains the relative positions between any 2 items
//
//This version reduces vector cloning by growing/shrinking the prefix vector
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip> //setw
#include <algorithm>  //sort
#include <assert.h>
using namespace std;
size_t calls=0, combos=0;
size_t const C=3; //how many in each combination
vector<char> emptyV;

template<typename T> void dump(vector<T> const & p, string const & s){
  cout<<"------------ "<<s<<" ------------ size = "<<p.size()<<endl;
  for(int i=0; i<p.size(); ++i) cout<<setw(5)<<p[i];
  if (p.size()) cout<<endl;
}
template<typename T> int show(vector<T> const * p, vector<T> const * v = NULL){
  ++ combos;
  stringstream ss;
  for(int i=0; i<p->size(); ++i) ss<<setw(5)<<(*p)[i];
  if (v){
    //cout<<",";
    for(int i=0; i<v->size(); ++i) ss<<setw(5)<<(*v)[i];
  }
  static string last("ZZZZZ");
  string combo=ss.str();
  cout<<"combo: "<<combo<<endl;
  assert(last >= combo);
  last = combo;
}

template<typename T> int recurs(vector<T> & prefix, vector<T> const & pool){// size_t const suffix ){
  ++calls;
  dump(prefix, "entering ... prefix"); dump(pool, "pool");
  if (prefix.size()            == C) return show(&prefix);
  if (prefix.size()+pool.size()== C) return show(&prefix, &pool);
  assert (!pool.empty());
  vector<T> const newPool(pool.begin()+1, pool.end());
  recurs(prefix, newPool);
  prefix.push_back(pool[0]);
  recurs(prefix, newPool);//this function returns only after all the layer are done
  prefix.pop_back();
}

int main() {
  string tmp = "abcde";
  vector<char> v(tmp.begin(), tmp.end());
  assert(C <= v.size());
  recurs(emptyV, v);
  cout<<calls<<"  calls to the recursive funcion to generate "<<combos<<endl;
}
