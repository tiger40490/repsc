// Requirement: generate all permutations of C(like 3) chars
//from N(like 5). The count should be N!/(N-C)!
// Bonus: generate in ascending order, where 'ascending' is
//defined on the basis that within the original word, a char
//has lower value than any char on its right. This is more clear
//when the word itself is a sorted string, but actually it's
//not needed.
//
//global collection is simpler than stack variables. Easier to visualize
//and uses less memory
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <assert.h>
using namespace std;

string _tmp="abcd"; vector<char> const pool(_tmp.begin(), _tmp.end());
vector<size_t> poolIndex;
size_t const C = 3, N = pool.size(); //wanted: all permutations of C, out of the pool of items

//global collection, to be updated in each recursive layer.
vector<vector<size_t> > coll;
// Note each item (like a char or a color or a studentId) is
// represented in the global collection by an unsigned integer.
// This is the positional index in the original "pool" of items.
// This scheme ensures the permutations produced is ascending

string show(vector<size_t> const & v, string headline="", bool isPrint=true){
  stringstream ss;
  for (int i=0; i<v.size(); ++i){
    ss<<setw(5)<<pool[v[i]];
  }
  if (isPrint) cout<<ss.str()<<" <-- "<<headline<<v.size()<<endl;
  return ss.str();
}
void dump(string headline="", bool isAssert=true){
  size_t const cnt = coll.size();
  assert(cnt);
  size_t const len = coll[0].size();
  size_t exp = 1; for (int t=N; t>N-len; --t) exp *= t; //loop len times
  assert(cnt == exp);

  stringstream ss;
  string last = "";
  for(int i=0; i<cnt; ++i){
    string item=show(coll[i], "", false);
    ss<<item<<endl;
    if (!isAssert) continue;
    assert(last<item && "should be strictly asending");
    last = item;
  }
  cout<<headline<<"\t size "<<cnt<<endl<<ss.str()<<endl;
}

//RVO should kick in to skip the copying upon return
vector<size_t> const find_unused(vector<size_t> const & perm, size_t const len){
      vector<size_t> tmp4set_diff(perm); //permutations are by defnition unsorted.
      sort(tmp4set_diff.begin(), tmp4set_diff.end());
      vector<size_t> unused(N-len);
      set_difference(poolIndex.begin(), poolIndex.end(), tmp4set_diff.begin(),tmp4set_diff.end(),unused.begin());
      //show(tmp4set_diff, "tmp4set_diff"); show(poolIndex, "poolIndex"); show(unused, "unused");
      return unused;
}

//RVO should kick in to skip the copying upon return
vector<size_t> const new_perm(vector<size_t> const & perm, size_t unused){
        vector<size_t> newPerm(perm);
        newPerm.push_back(unused);
        //show(newPerm, "newPerm");
        return newPerm;
}
//This algo is considerably more complex than many recursive algos
//we have written recently, largely due to the set_difference()
void next_perm_from_pool_iterative(){
  for(size_t loop=0;loop<9 /*useful during dev to control when to exit*/;++loop){
    if (coll.empty()){
      for(size_t j=0; j<pool.size(); ++j){
        coll.push_back(vector<size_t>(1, j));
        poolIndex.push_back(j);
      }
      // dump("^^^^ after initilization of coll ^^^^");
    }
    assert(!coll.empty());
    size_t const len=coll[0].size();
    assert(loop+1 == len);
    if (len == C) {
      cout<<"Done:)"<<endl;
      return;
    }
    vector<vector<size_t> > newcoll;
    for(int kk=0; kk<coll.size(); ++kk){
      vector<size_t> const & perm = coll[kk];
      vector<size_t> unused(find_unused (perm, len));

      //now unused contains the pool items not in the current perm.
      //Suppose there are 3 unused items, we will create 3 new permutations
      //by appending each one to the current perm
      for(vector<size_t>::iterator it=unused.begin(); it != unused.end(); ++it){
        newcoll.push_back(new_perm(perm, *it));
      }
    }
    coll = newcoll;
    dump("^^^^ end of iteration ^^^^");
  }
}

int main(){
  next_perm_from_pool_iterative();
}
