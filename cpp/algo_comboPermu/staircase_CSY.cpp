/*
todo: figure out why pow(2, staircase-1)
showcase: ctor call on vector , via a type alias Path
*/
#include <vector>
#include <queue>
#include <numeric>
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
  bool isVerbose = staircase < 8;
  queue<Path> q; q.push(Path());
  for (int cnt=0;;++cnt){
    if (q.empty()){
      assert( pow(2,staircase-1) == cnt);
      cout<<staircase<<"-level staircase: returning "<<cnt<<endl;
      return cnt;
    }
    Path pa=q.front(); q.pop();
    Length gap = staircase - accumulate(pa.begin(), pa.end(), 0);
    assert(gap > 0);
    for (Length step=1; step<gap; ++step){ 
      q.push(pa); //vector clone
      q.back().push_back(step); //append on the cloned vector
    }
    pa.push_back(gap); //a complete path
    if (isVerbose){
      assert( accumulate(pa.begin(), pa.end(), 0) == staircase && "a complete path must have total length == staircase");
      cout<<":)"<<pa; 
    }
  } //for
}

int main(){
  solBFT(4);
  solBFT(5);
  solBFT(7);
  solBFT(13);
}/*Req: https://wp.me/p74oew-61P count how many ways to climb a staircase of length N
*/