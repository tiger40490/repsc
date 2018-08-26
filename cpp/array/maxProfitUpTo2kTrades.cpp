/* showcase 
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
   //for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   //os<<endl;
   return os;
}
using Price=int;
using Profit=int;
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

int sol1(vector<Price> const orig, size_t const topN=2){
  vector<Price> v;
  v.push_back(orig[0]);
  for (int i=1; i<orig.size(); ++i){
    if (orig[i-1] != orig[i]) v.push_back(orig[i]);
  } //all flats removed
  vector<Rec> zigzag;
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
  
  vector<Profit> profits;
  for (int i=1; i<zigzag.size(); i +=2){
    profits.push_back(zigzag[i].val - zigzag[i-1].val);
  }
  sort(profits.begin(), profits.end());
  reverse(profits.begin(), profits.end());
  ss<<"profits: "<<profits;
  
  Profit ret=0;
  for (int i=0; i<topN && i<profits.size(); ++i){
    ret += profits[i];
  }
  return ret;
}
int main(){
  assert(6+7==sol1({1,2,4,2,5,7,2,4,9,0}));
  //assert(14+2==sol1({1,13,12,14,13,15,14,16,5}));
  //assert(6==sol1({3,3,5,0,0,3,1,2,4}));
  //assert(6==sol1({4,3,5,0,0,3,1,2,4}));
  //assert(0 == sol1({7,5,4,2,1}));
  //assert(18==sol1({2,3,5,0,10,15,11,4}));
}
/*Requirmenet and design: https://wp.me/p74oew-62k
*/