/*
todo: clean-up
todo: figure out why pow(2, staircase-1)
*/
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
using namespace std;

template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
using Length=int;
using Path=vector<Length>;
int solBFT(Length staircase){
  bool isVerbose = staircase < 7;
  queue<Path> q; q.push(Path());
  int cnt=0;
  for (;!q.empty();){
    Path pa=q.front(); q.pop();
    Length gap = staircase;
    for (Length step: pa) 
      gap -= step;
    //cout<<gap<<" = gap "<<pa;
    assert(gap > 0);
    for (Length step=1; step<gap; ++step){ //if gap is 2 then append 1.. 2 
      auto newpa(pa);
      newpa.push_back(step);
      q.push(newpa);
    }
    pa.push_back(gap);
    if (isVerbose) cout<<":)"<<pa;
    ++cnt;
  }
  assert( pow(2,staircase-1) == cnt);
  cout<<staircase<<"-level staircase: returning "<<cnt<<endl;
  return cnt;
}

int main(){
  solBFT(5);
  solBFT(9);
  solBFT(13);
}/*Req: https://wp.me/p74oew-61P
*/