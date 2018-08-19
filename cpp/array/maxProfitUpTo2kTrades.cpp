/* showcase 
*/
#include <vector>
#include <iostream>
#include <iomanip>
#include <assert.h>
#define ss if(2>1) cout
using namespace std;

template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   os<<" ";
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width+2)<<i<<" "; }
   os<<endl;
   return os;
}
typedef int Num;
struct Rec{
  Num val;
  bool hi;
  bool lo;
  Rec(Num a, bool h): val(a), hi(h), lo(!h){}
  friend ostream & operator<<(ostream & os, Rec const & r){
    os<<r.val;
    if (r.hi) os<<"^ ";
    else      os<<"v ";
  }
};

int sol1(vector<Num> const orig){
  vector<Num> v;
  v.push_back(orig[0]);
  for (int i=1; i<orig.size(); ++i){
    if (orig[i-1] == orig[i]) continue;
    v.push_back(orig[i]);
  } //all flats removed
  vector<Rec> arr;
  if (v[0]<v[1]) arr.push_back(Rec(v[0], false));
  for (int i=1; i<v.size()-1; ++i){
    if ( (v[i-1]-v[i]) * (v[i]-v[i+1]) >=0) continue;
    arr.push_back(Rec(v[i], v[i-1]<v[i]));
    //ss<<v[i]<<" saved\n";
  }
  Num last = v[v.size()-1];
  auto & tmp = arr[arr.size()-1];
  if     (tmp.lo && tmp.val < last)
    arr.push_back(Rec(last, true));
  else if(tmp.hi && tmp.val > last)
    arr.push_back(Rec(last, false));
  ss<<arr;
}
int main(){
  assert(sol1({3,3,5,0,0,3,1,2,4}));
  //assert(sol1({4,3,5,0,0,3,1,2,4}));
}
/*Requirmenet: 

*/
