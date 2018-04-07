//what if all the way down?
#include <iostream>
#include <vector>
typedef double Px;
typedef size_t Ts; //timestamp

void solve(vector<Px> a){
  //deal with singlular vectors...
  map<Ts, bool> trades; //yes = buy; no = Sell
  for(Ts i=0, bool isUp=; i<a.size(); ++i){
    
  }
}
int main(){
  solve({7,2,5,3,9});
}
/* Requirement: https://bintanvictor.wordpress.com/2018/04/07/best-day-trading-play-in-hindsight-nasdaq/
Strategy: every time we see a downturn, we sell (every upturn, we buy). 

If the trades collection has matched buys/sells, then we need to add a pair of buy/sell at the two ends...

If the trades collection has an extra sell (buy), then both extreme ends point down(up) so we pick the lower(higher) between the two. 
*/