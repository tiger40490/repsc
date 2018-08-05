#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;
typedef unsigned int idx;
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
int maxArea(vector<int>& height) {
  cout<<height;
  idx le = 0,   ri = height.size()-1; //the walls
  idx lem = le, rim=ri; // the moving markers
  //int distance=rim-le; //distance between lem and the opposite wall
  for(int ret = (ri-le)*min(height[le], height[ri]);;){
    if (lem+1 == rim){ 
      cout<<"returning "<<ret<<endl;
      return ret;
    }
    int area=0;
    if (height[le] <= height[ri]){
      ++lem; 
      cout<<"moving lem --> "<<lem<<endl;
      if (height[le] >= height[lem]) continue; //nothing to do
      le = lem;
      // no.... if (height[lem] > height[ri]) le = lem;
    }else{
      --rim;
      cout<<rim<<" <-- moving rim"<<endl;
      if (height[rim] <= height[ri]) continue; //nothing to do
      ri = rim;
    }
    area = (ri-le)*min(height[le], height[ri]);
    cout<<area<<" = new area computed\n";
    if (ret < area) ret = area;
  }
}
void test1(int expected, vector<int> v){
  assert(expected == maxArea(v));
}
int main(){
  test1(40, {5,9,5,3,4,0,8,5,2});
}/*Req: Given an array of size N (>=2) of non-negative numbers representing N walls, find a pair of walls trapping the most rain water.
Here's a rewrite based on the rainfall_Boris idea.

*/