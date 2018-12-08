/* 
todo: implement the other solutions

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
using id=size_t; //index into letters<T>
size_t L, changes=0, calls=0;
size_t C; //how many in each combination
//set<int> const AllChoices({11,22,33,44,55});
set<char> const AllChoices({'a','b','c','d','e'});
vector<decltype(AllChoices)::value_type> letters;

template<typename ITR> bool isAscending (ITR const b, ITR const end){
  for (ITR last = b, i = b; i!=end; ++i){
    if (*last > *i) {
      cout<<*last<<" should be lower (or equal) but is higher than "<<*i<<endl;
      return false;
    }
  }
  return true;
}
void dump(vector<id> & v,  bool isAssert = true){
  for(int i=0; i<v.size(); ++i) {
    cout<<setw(5)<<letters[v[i]];
  }
  cout<<endl;
  if(isAssert){
    assert(isAscending(v.begin(), v.begin()+C) && "1st C elements should be ascending after next_combo (not next_perm)");
  }
}
bool next_combo(vector<id> & v){
  ++calls;
  dump(v );
  for(int p2u=C-1; /*last position*/ p2u >=0 ;--p2u){
    if (v[p2u] == L-1) continue;
    //cout<<"identified "<<p2u<<" as position to upgrade... and return"<<endl;
    id const nextChoice = v[p2u]+1;
    for (; p2u<C; ++p2u) v[p2u] = nextChoice;
    return true;
  }//for
  cout<<"no more higher combo. This is the end"<<endl;
  return false;
}
template<typename T> int test1(int le, int repeat, set<T> coll){
  vector<T> vec1(coll.begin(), coll.end());
  C = repeat;    L = le;
  letters.assign(vec1.begin(), vec1.begin()+le);
  vector<id> v(C, 0); //first combo
  for(calls=0; calls<9999; ){
      if (!next_combo(v)){
         cout<<changes<<" changes performed till the highest combo; next_combo() call count = "<<calls<<endl;
         return calls;
      }
  }
  assert(1==0);
}
int main() {
  assert (10==test1(4,2, AllChoices));
  assert (4 ==test1(2,3, AllChoices));
  assert (10==test1(3,3, AllChoices));
  assert (15==test1(3,4, AllChoices));
  assert (21==test1(3,5, AllChoices));
}/* req: For L letters printed on a single button, after pressing C times, how many possible combinations? Better list them in ascending order
*/