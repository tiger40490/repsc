/*
todo: implement a bottom-up DP solution
todo: implement a top-down recursive solution with memoization
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
int solBFT(Length staircase){ //by myself, not CSY. Longer than the standard solution but fairly efficient and versatile technique. 
// :( no duplicate paths, probably due to the tree structure
// :( No memoization required because non-recursive
// :) the total count of 2^(n-1) is hard to see
  bool isVerbose = staircase < 8;
  queue<Path> q; q.push(Path()); //empty path
  for (int cnt=0;;++cnt){ //a variation of while(BFT queue not empty)
    if (q.empty()){
      assert( pow(2,staircase-1) == cnt);
      cout<<staircase<<"-level staircase: returning "<<cnt<<endl;
      return cnt;
    }
    Path pa=q.front(); q.pop();
    Length gap = staircase - accumulate(pa.begin(), pa.end(), 0);
    assert(gap > 0); // gap can be saved with path, in a wrapper struct 
    for(Length step=1; step<gap; //Note step never grows to Equal gap. Equal means a complete path
          ++step){
      q.push(pa); //vector clone to create new, incomplete path
      q.back().push_back(step); //enqueue the cloned path
    }
    pa.push_back(gap); //a complete path created for every pop()
    if (isVerbose){
      assert( accumulate(pa.begin(), pa.end(), 0) == staircase && "a complete path must have total length == staircase");
      cout<<":)"<<pa; 
    }
  } //for
}

int main(){
  solBFT(5);
  solBFT(7);
  solBFT(13);
  solBFT(4);
}/*Req: https://wp.me/p74oew-61P count how many ways to climb a staircase of length N
*/
