// showcase integer-ratio simplication using GreatestCommonDenominator algo.
// showcase to_string from integer
#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int sgn(int v) {
  if (v==0) return 0;
  return abs(v)/v; // less efficient but easy to reproduce in speed coding
}
unsigned int gcd(int u, int v){//recursive
  u=abs(u); v=abs(v);
  return (v == 0) ? u : gcd(v, u % v);
}
// returns the first point (C) encountered after turning right 90 degrees
string solution(int ax, int ay, int bx, int by){
  int dy=by-ay, dx=bx-ax;
  if      (dy==0){
      dy = -sgn(dx);
      dx=0; // cx == bx
  }else if(dx==0){
      dx = sgn(dy);
      dy=0; // cy == by
  }else{  
    size_t tmp=gcd(dy, dx);
    dy /= tmp; 
    dx /= tmp;
    cout<<dy<<"/"<<dx<<" after simplifying the ratio representing the slope\n";
    swap(dy,dx);
    dy = -dy;
    cout<<dy<<"/"<<dx<<" after swap and negate\n";
  }
  return to_string(bx+dx) +"," +to_string(by+dy);
}

int main(){
  assert("1,-3" == solution(2,2,2,-3)); //orig 
  assert("2,-1" == solution(-1,3,3,1)); //orig 
  assert("-2,1" == solution(3,1,-1,-1)); //-1-1, -1+2
}/*Req: given a 2D grid (i.e. all intersection having signed integer coordinates), starting from intersection A(ax,ay) moving to intersection B(bx,by), and turning right 90 degrees, what's the first intersection encountered?
*/
