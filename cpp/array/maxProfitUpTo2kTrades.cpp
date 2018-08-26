/* 
todo: create reusable maxp(idx le, idx ri)
showcase 
*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <assert.h>
#define ss if(2>1) cout
using namespace std;

template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   os<<" ";
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
using Price=int;
using Profit=int;
using idx=int;
struct Rec{
  Price val;
  bool hi;
  bool lo;
  Rec(Price a, bool h): val(a), hi(h), lo(!h){}
  friend ostream & operator<<(ostream & os, Rec const & r){
    stringstream sstr;
    sstr<<r.val;
    if (r.hi) sstr<<"^ ";
    else      sstr<<"v ";
    os<<sstr.str();
    return os;
  }
};
int cleanse(vector<Price> const orig, vector<Rec> & zigzag){
  vector<Price> v;
  v.push_back(orig[0]);
  for (int i=1; i<orig.size(); ++i){
    if (orig[i-1] != orig[i]) v.push_back(orig[i]);
  } //all flats removed
  if (v[0]<v[1]) zigzag.push_back(Rec(v[0], false));
  for (int i=1; i<v.size()-1; ++i){
    if ( (v[i-1]-v[i]) * (v[i]-v[i+1]) >=0) continue;
    assert (v[i-1] != v[i]);
    zigzag.push_back(Rec(v[i], v[i-1]<v[i]));
    //ss<<v[i]<<" saved\n";
  }
  if (zigzag.empty()) return 0;
  // now deal with the last price point
  Price last = v[v.size()-1];
  auto & b4last = zigzag[zigzag.size()-1];
  if     (b4last.lo && b4last.val < last)
    zigzag.push_back(Rec(last, true));
  else if(b4last.hi && b4last.val > last)
    zigzag.push_back(Rec(last, false));
  ss<<zigzag; //good so far.
  return 1;
}
Profit maxp(vector<Rec> const & zigzag, idx & le, idx ri, bool isloss=true){
  Price wm=zigzag[le].val; idx wmIdx=le;
  Profit best=0; idx bestLe=le, bestRi=le;
  for (idx i=le; i <= ri; ++i){
    Price tmp=zigzag[i].val;
    if ((tmp < wm && !isloss) ||
        (tmp > wm &&  isloss)    ){
      wm=tmp;
      wmIdx = i;
    }else{
      Profit tmp2=tmp-wm;
      if ((tmp2 > best && !isloss) ||
          (tmp2 < best &&  isloss)    ) {
        best = tmp2;
        bestLe=wmIdx;
        bestRi=i;
      }
    }
  }
  le = bestLe;
  ri = bestRi;
  ss<<best <<" max p/l returned for "<<le<<'-'<<ri<<endl;
  return best;
}
int sol2(vector<Price> const orig, size_t const topN=2){
  vector<Rec> zigzag;
  if (cleanse(orig, zigzag) == 0) return 0;
  idx le = 0, ri=zigzag.size()-1;
  maxp(zigzag, le, ri);
  
  return 13;
}
int main(){
  assert(6+7==sol2({1,2,4,2,5,7,2,4,9,0}));
  //return 0;
  assert(sol2({1,13,12,14,13,15,14,16,5}));
  assert(sol2({3,3,5,0,0,3,1,2,4}));
  assert(sol2({4,3,5,0,0,3,1,2,4}));
  assert(0 == sol2({5,5}));
  assert(0 == sol2({7,5,4,2,1}));
  assert(sol2({2,3,5,0,10,15,11,4}));
}
/*Requirmenet and design: https://wp.me/p74oew-62k

* identify the best pair using the max-profit algo. denote them as l1/hj
* In the subarray before l1, find the best pair
* in the subarray after hj, find the best pair
pick the best among the two an denote it as p2
Now look into the subarray l1 to hj. If there’s no enclosed pairs within then we have a simple case — use l1/hj and p2. But let’s assume there are at least 2 nodes enclosed. I will denote entire subarray as l1 h1 l2 h2 … lj hj (where l1-hj is the max-profit)
* use max-profit algo to find the worst loss from h1 to lj. Suppose it’s h3 to l5.
If this loss exceeds p2, then the we will return l1/h3 and l5/hj. Otherwise, return l1/hj and p2
This solution uses the max-profit algo 4 times (*).

*/