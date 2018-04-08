//what if all the way down?
//if price didn't change, then remove that print point
//if direction doesn't change, then remove intermediate print points
//if no turning point at all, then no profit to make
//showcase using map to erase ... more robust than deque/vector when erasing
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <iterator>
using namespace std;
typedef double Px;
typedef size_t Ts; //timestamp
void dump(vector<Px> const & a, string headline=""){  
  cout<<"-------- "<<headline<<" .. size == "<<a.size()<<endl;
  auto const sz = a.size();
  for(Ts i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
  
  for(Ts i=0; i<sz; ++i) {
    cout<<a[i]<<"\t";
  }cout<<endl;
}

void shrink(vector<Px> & a){ //remove useless points
  //bool /*wasRising*/ wr; //uninitialized!
  for(auto it=next(a.begin()); it!=prev(a.end());){
    Px const pp = *prev(it);
    Px const nn = *next(it);
    Px const ii = *it;
    //cout<<ii<<" is the current price"<<endl;
    if ((pp - ii) * (ii - nn) >= 0){
      it=a.erase(it);
      //dump(a, "after erasing the current price");
    }else{
      ++it;
    }
    //wr = (a[0]<===a[1]);
    //bool isRising = a[i]<a[i+1];
  }
}

int solve(vector<Px> a){ //return total profit
  if (a.size() < 2) return 0;
  shrink(a);
  dump(a, "after shrink");
  
  map<Ts, bool> trades; //yes = buy; no = Sell
  //for(Ts i=1, bool /*wasRising*/ wr= (a[0]<=a[1]); i<a.size(); ++i){ }
}
int main(){
  solve({4,5,3,6,1,2});
  solve({4,4,5, 4.11, 3, 4.22, 6,6,2,1,2});
}
/* Requirement: https://bintanvictor.wordpress.com/2018/04/07/best-day-trading-play-in-hindsight-nasdaq/
Strategy: every time we see a downturn, we sell (every upturn, we buy). 

If the trades collection has an extra sell (buy), then both extreme ends point down(up) so we pick the lower(higher) between the two. 

If the trades collection has matched buys/sells, then we need to add a pair of buy/sell at the two ends. Be careful.

*/