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
size_t cleanse(vector<Price> const orig, vector<Rec> & zigzag){
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
  return zigzag.size();
}
Profit maxp(vector<Rec> const & zigzag, idx& le, idx& ri, bool isloss=false){
  if (ri<=0){
    le=ri=0;
    ss<<" max p/l = 0 at right end "<<le<<'-'<<ri<<endl;
    return 0;
  }
  idx sz=zigzag.size();
  if (le>=sz-1){
    le=ri=sz-1;
    ss<<" max p/l = 0 at left end "<<le<<'-'<<ri<<endl;
    return 0;
  }
  if (ri+1==le){
    le=ri;
    ss<<" max p/l = 0 cos Max Profit section must have size==2! "<<le<<'-'<<ri<<endl;
    return 0;  
  }
  assert (le <= ri);
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
  ss<<best <<" = max p/l returned for "<<le<<'-'<<ri<<endl;
  return best;
}
int sol2(vector<Price> const orig, size_t const topN=2){
  vector<Rec> zigzag;
  if (cleanse(orig, zigzag) < 2) return 0; //fewer than 2 nodes
  int sz=zigzag.size();
  idx le1 = 0, ri1=sz-1;
  maxp(zigzag, le1, ri1);
  idx leIn=le1+1, riIn=ri1-1;
  Profit maxpIn=maxp(zigzag, leIn, riIn, true);
  
  //now fine 2nd best pair from left and right section
  idx leB4=0, riB4=le1-1;
  Profit maxpB4=maxp(zigzag, leB4, riB4);
  idx leAf=ri1+1, riAf=sz-1;
  Profit maxpAf=maxp(zigzag, leAf, riAf);
  
  return 13;
}
int main(){
  assert(sol2({2,3,5,0,10,15,11,4,7}));
  assert(6+7==sol2({1,2,4,2,5,7,2,4,9,0}));
  //return 0;
  assert(sol2({1,13,12,14,13,15,14,16,5}));
  assert(sol2({3,3,5,0,0,3,1,2,4}));
  assert(sol2({4,3,5,0,0,3,1,2,4}));
  assert(0 == sol2({5,5}));
  assert(0 == sol2({7,5,4,2,1}));
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