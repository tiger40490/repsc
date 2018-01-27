/*
–Solution 1: std::next_permutation() and prev_permutation()
–solution 2: I can probably write my own next_perm(). Using This function we can generate an ascending sequence of permutations starting from the current content of a vector.
*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <assert.h>
using namespace std;
static size_t changes=0, calls=0;

template<typename T> void dump(vector<T> & v){
  for(int i=0; i<v.size(); ++i) cout<<setw(3)<<v[i];
  cout<<endl;
  for(int i=0; i<v.size(); ++i) cout<<setw(3)<<i;
  cout<<endl<<"----------------------------"<<endl;
}

// reshuffles vector to the next higher permutation
// the items in vector don't need to be unique
template<typename T> bool next_perm(vector<T> & v){
  ++calls;
  dump(v);
  if (v.size() == 1) return false;
  int p2u=v.size()-2; //2nd last position
  assert(p2u>=0);
  for(;;--p2u){
    if (v[p2u] >= v[p2u+1]){ //p2u till end is the highest permutation possible
      if (p2u>0) continue;
      assert(p2u == 0);
      cout<<"no more higher permutation. This is the end"<<endl;
      return false;
    }
    //cout<<"identified position to upgrade as "<<p2u<< " ... Will rearrange the items and return"<<endl;

    //should upper_bound or lower_bound
    for (int swp=v.size()-1; ; --swp){
      if ( v[p2u] >= v[swp]) continue;
      swap(v[swp], v[p2u]);
      sort(v.begin()+p2u+1, v.end()); // range to reset is p2u+1 till end
      //dump();
      ++changes;
      return true;
    }
  }
}
int main() {
  vector<char> v{'a', 'b', 'b', 'c' , 'd'};
  while (next_perm(v)){ }
  cout<<changes<<" changes performed till the highest permutation; next_perm() call count = "<<calls<<endl;
}
