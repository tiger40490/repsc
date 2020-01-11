#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int sgn(int v) {
  if (v < 0) return -1;
  if (v > 0) return 1;
  return 0;
}
unsigned int gcd(int u, int v){
  u = abs(u); v=abs(v);
    return (v != 0) ? gcd(v, u % v) : u;
}
string solution(int ax, int ay, int bx, int by){
  int dy=by-ay, dx=bx-ax;
  if (dy*dx ==0){
    if (dy==0){
      //by +/- 1
      //bx is the nex x
      dy = -sgn(dx);     
      dx=0;
    }else {
      dx = sgn(dy);
      dy=0; //by is the new y
      cout<<dy<<"/"<<dx<<" when vertical\n";
    }
  }else{  
    //simplfy ratio ,,, actually can find a point closer to B
    size_t tmp=gcd(dy, dx);
    dy /= tmp; 
    dx /= tmp;
    cout<<dy<<"/"<<dx<<" after simplify\n";
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
}
