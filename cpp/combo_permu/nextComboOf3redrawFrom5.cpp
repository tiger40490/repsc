/* 
showcase decltype on a container object to extract element type
showcase vector::assign(itr, itr) instead of clear() then insert(itr, itr)

Without loss of generality, each combination is internally represented as a sorted vector (ascending). There's one-to-one mapping between such a vector and a combination
*/
#include <iostream>
#include <vector>
#include <set>
#include <iomanip> //setw
#include <algorithm>  //sort
#include <assert.h>
using namespace std;
using ID=size_t; //index into letters<T>
size_t L, changes=0, calls=0;
size_t C; //how many in each combination
//set<int> const AllChoices({11,22,33,44,55});
set<char> const AllChoices({'a','b','c','d','e'});
vector<decltype(AllChoices)::value_type> letters;

template<typename ITR> bool isAscending (ITR const b, ITR const end){
  //cout<<*b<<" < - > "<<*end<<endl;
  for (ITR last = b, i = b; i!=end;){
    //cout<<*i<<endl;
    if (*last > *i) {
      cout<<*last<<" should be lower (or equal) but is higher than "<<*i<<endl;
      return false;
    }
    last = i;
    ++i;
  }
  return true;
}
void dump(vector<ID> & v,  bool isAssert = true){
  for(int i=0; i<v.size(); ++i) {
//    cerr<<setw(5)<<letters[v[i]];
    cerr<<setw(5)<<v[i];
  }
  cout<<endl;
  if(isAssert){
    assert(isAscending(v.begin(), v.end()) && "1st C elements should be ascending after next_combo (not next_perm)" );
  }
}
//Solution N, yielding the next higher combination
bool next_combo(vector<ID> & v){
  ++calls;
  dump(v );
  for(int p2u=C-1; /*last position*/ p2u >=0 ;--p2u){
    if (v[p2u] == L-1) continue;
    //cout<<"identified "<<p2u<<" as position to upgrade... and return"<<endl;
    ID const nextChoice = v[p2u]+1;
    for (; p2u<C; ++p2u) v[p2u] = nextChoice;
    return true;
  }//for
  cout<<"no more higher combo. This is the end of next_combo()"<<endl;
  return false;
}
//solution A, based on appending
set<vector<ID>> combos;
int solA(){
  combos.clear();
  for (ID i=0; i<L; ++i) combos.insert(vector<ID>({i})); //initialized
  for(size_t sz=1; sz < C; ++sz){
    set<vector<ID>> newCombos;
    for (auto const & v: combos){ //solA to v
      for (ID tip = v[v.size()-1]; tip < L; ++tip){
        vector<ID> newV(v);
        newV.push_back( tip );
        newCombos.insert(newV);
        dump(newV);
      }
    }
    combos = newCombos;
  }
  cout<<"-----end of solA() ----\n";
  return combos.size();
}
template<typename T> int test1(int le, int repeat, set<T> coll){
  vector<T> vec1(coll.begin(), coll.end());
  C = repeat;    L = le;
  letters.assign(vec1.begin(), vec1.begin()+le);
  int const ret = solA();
  vector<ID> v(C, 0); //first combo
  for(calls=0; calls<9999; ){
      if (!next_combo(v)){
         cout<<changes<<" changes performed till the highest combo; next_combo() call count = "<<calls<<endl;
         assert (ret == calls);
         return calls;
      }
  }
  assert(1==0);
}
int main() {
  assert (4 ==test1(2,3, AllChoices));
  assert (10==test1(4,2, AllChoices));
  assert (10==test1(3,3, AllChoices));
  assert (15==test1(3,4, AllChoices));
  assert (21==test1(3,5, AllChoices));
}/* req: For L letters printed on a single button, after pressing C times, how many possible combinations? Better list them in ascending order
*/
