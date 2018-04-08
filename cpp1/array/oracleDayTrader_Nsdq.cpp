//showcasing vector erase while iterating
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <iterator>
#include <assert.h>
using namespace std;
typedef double Px;
typedef size_t Ts; //timestamp
typedef bool BS;
Ts sz=0;
double dump(map<Ts, BS>  const & trades, vector<Px> const & a, string headline=""){  
  double accu = 0;
  auto fi=trades.begin();
  for (auto ri=trades.rbegin();
       fi->first < ri->first; ++fi, ++ri){
    assert(fi->second != ri->second);
    accu += a[fi->first] * (fi->second ?-1:1);
    accu += a[ri->first] * (ri->second ?-1:1);
  }
  cout<<"-------- "<<headline<<" .. total profit = $"<<accu<<endl;
  for (auto it=trades.begin(); it!=trades.end(); ++it){
    cout<<it->first<<":"<<(it->second? "B":"S")<<" $"<<a[it->first]<<"\t";
  }cout<<endl;
  return accu;
}
void dump(vector<Px> const & a, string headline=""){  
  cout<<"-------- "<<headline<<" .. size == "<<a.size()<<endl;
  auto const sz = a.size();
  for(Ts i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
  for(Ts i=0; i<sz; ++i) cout<<a[i]<<"\t";
  cout<<endl;
}
void shrink(vector<Px> & a){ //remove useless points
  for(auto it=next(a.begin()); it!=prev(a.end());){
    if ((*prev(it) - *it) * (*it - *next(it)) >= 0){ it=a.erase(it);
    }else{ ++it; }
  }
  int i=1; //can't put into for-loop header !
  for(auto it=next(a.begin()); it!=prev(a.end()); ++it, ++i){
    //cout<<"Every prince point should be a turning point... Checking tiomestamp # "<<i<<endl; 
    assert ((*prev(it) - *it) * (*it - *next(it)) < 0);
  }  
}
void wrapUp(vector<Px> & a, map<Ts, BS> & trades){
  if (trades.size()%2 == 0){// If the trades collection has matched buys/sells, then we need to add a pair of buy/sell at the two ends. 
      if (a[0]==a[sz-1]) return;
      trades.insert(make_pair(0,   a[0]<a[sz-1]));
      trades.insert(make_pair(sz-1,a[0]>a[sz-1]));
      return;
  }
  //if first trade is buy, then we need a sell at higher of the two ends
  bool closingHigher = a[0]<=a[sz-1];
  BS buyNeeded = !trades.begin()->second;
 
  if (closingHigher && !buyNeeded ||
     !closingHigher &&  buyNeeded ){ 
    trades.insert(make_pair(sz-1, !trades.begin()->second)); //add an reverse of the first trade
  }else{
    trades.insert(make_pair(0, !trades.begin()->second)); 
  }
}
int solve(vector<Px> a){ //return total profit
  if (a.size() < 2) return 0;
  shrink(a); dump(a, "after shrink");
  
  sz=a.size();
  map<Ts, BS> trades; //yes = buy; no = Sell
  for(Ts i=1; i<sz-1; ++i){ 
    trades.insert(make_pair(i,   a[i-1]>a[i])); //was falling=>buy
    //cout<<ii<<" is the current price"<<endl;
  }
  dump(trades, a, "b4 wrapUp");
  wrapUp(a, trades);
  dump(trades, a, "final");
}
int main(){
  //solve({4,5,3,6,1,2});
  solve({4,4,5, 4.11, 3, 4.22, 6,6,2,1,2});
}
/* Requirement: https://bintanvictor.wordpress.com/2018/04/07/best-day-trading-play-in-hindsight-nasdaq/
Strategy: every time we see a downturn, we sell (every upturn, we buy). 

If the trades collection has an extra sell (buy), then both extreme ends point down(up) so we pick the lower(higher) between the two. 

*/