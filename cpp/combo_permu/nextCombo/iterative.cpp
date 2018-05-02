//Without loss of generality, each combination is internally represented
//as a sorted vector (ascending).
//There's one-to-one mapping between such a vector and a combination
#include <iostream>
#include <vector>
#include <iomanip> //setw
#include <algorithm>  //sort
#include <assert.h>
using namespace std;
size_t changes=0, calls=0;
size_t const C=3; //how many in each combination

template<typename ITR> bool isAscending (ITR const b, ITR const end){
  for (ITR last = b, i = b; i!=end; ++i){
    if (*last > *i) {
      cout<<*last<<" should be lower (or equal) but is higher than "<<*i<<endl;
      return false;
    }
  }
  return true;
}
template<typename T> void dump(vector<T> & v,  bool isAssert = true){
  for(int i=0; i<v.size(); ++i) {
    cout<<setw(5)<<v[i];
    if (i == C-1) cout<<"  unused:";
  }
  cout<<endl;
  for(int i=0; i<v.size(); ++i){
    cout<<setw(5)<<i;
    if (i == C-1) cout<<"  unused:";
  }
  cout<<endl<<"---------------------------------"<<endl;
  if(isAssert){
    assert(isAscending(v.begin(), v.begin()+C) && "1st C elements should be ascending after next_combo (not next_perm)");
    assert(isAscending(v.begin()+C+1, v.end()) && "unused section should be ascending");
  }
}

template<typename T> bool reshuffle(vector<T> & v, int p2u){
//      cout<<"after swap"<<endl; dump(v);
        sort(v.begin()+p2u+1, v.end());
//      cout<<"after sorting everyting to the right of p2u"<<endl; dump(v);

        if (p2u == C-1){
                sort(v.begin()+C, v.end());
                ++changes;
                return true;
        }
        assert(p2u<C-1);
        //now reset everything to my right
        //now locate the best_man (next item after the new p2u) .. can use binary search
        for(int i=p2u+1; i<v.size() ; ++i){
          if (i==v.size()){ //p2u is highest possible!
                //cout<<"p2u is already highest"<<endl;
                sort(v.begin()+C, v.end());
                ++changes;
                return true;
          }
          if (v[p2u]<v[i]){
                //cout<<"best man = "<<i<<endl;
                for(int j=0; p2u+1+j<=C-1; ++j){
                  swap(v[p2u+1+j], v[i+j]);
                }
                sort(v.begin()+C, v.end());
                ++changes;
                return true;
          }
        }//for
        // now must return!

        assert(1==0 && "should never reach here");
        cout<<"after best_man search"<<endl; dump(v);
}

// reshuffles vector to the next higher combo
//Assuming 5-choose-3, the 1st 3 chars represent the combination,
//and the remaining characters at the end of the vector are
//unused in the current combination.
template<typename T> bool next_combo(vector<T> & v){
  ++calls;
  dump(v );
  if (v.size() == C) return false; // C-choose-C == 1 !

  for(int p2u=C-1; /*last position*/ p2u >=0 ;--p2u){
    for (int unusedItem=C; unusedItem<v.size(); ++unusedItem){ //scan the unused section of the array
        if (v[p2u] < v[unusedItem]) {
          assert(p2u<unusedItem);
          swap(v[p2u], v[unusedItem]);  //p2u should not change further
        //cout<<"identified "<<p2u<<" as position to upgrade... Will reset subsequent positions, and return"<<endl;
          return reshuffle(v, p2u);
        }
    }
    // no p2u identified yet. move p2u marker to the left
  }//for
  cout<<"no more higher combo. This is the end"<<endl;
  return false;
}
int main() {
//  vector<float> v{111,222,333,444,555,666};
  string tmp = "abcdefg";
  vector<char> v(tmp.begin(), tmp.end());
  assert(C <= v.size());
  for(; calls<9992; ){
        if (!next_combo(v)){
         cout<<changes<<" changes performed till the highest combo; next_combo() call count = "<<calls<<endl;
         return 0;
        }
  }
}
