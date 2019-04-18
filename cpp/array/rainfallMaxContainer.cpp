/*todo: 
*/
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
using namespace std;
typedef unsigned int idx;
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(size_t i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
/*I keep 4 moving pointers mostly to avoid overhead. When the low-side pointer moves in and hits a very low wall, I can skip recalc and keep moving it, but need to remember the low-side best wall.
*/
int maxAreaMyAlgo(vector<int>& height) {
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
    
    //We can have more granular cases than these two. For some problems like trapping rain water, we might need them. Overkill for this case. Overall, the more granular technique is reusable and valuable.
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
    assert(ri==rim && le==lem);
    area = (ri-le)*min(height[le], height[ri]);
    cout<<area<<" = new area computed\n";
    if (ret < area) ret = area;
  }
}
int maxAreaCSY(vector<int> const & height) {
  cout<<height;
  for (int max=0, left=0, right=height.size()-1;;){    
    if (left == right) return max;
    int vol = (right-left)*min( height[left], height[right] );
    if (vol > max){      max = vol;}      //leftBest=left; rightBest=right;
    
    if (height[left] <= height[right]) left++;
    else right--;
  }
}
void test1(int expected, vector<int> v){
//  assert(expected == maxAreaMyAlgo(v));
  assert(expected == maxAreaCSY(v));  
}
int main(){
  test1(7, {7,9});
  test1(56, {7,1,9,9,5,4,9,5,7});
  test1(40, {5,9,5,3,4,0,8,5,2});
}/*Req: Q: Given an array of size N (>=2) of non-negative numbers representing N walls, find a pair of walls that can hold the most water.

This is a rewrite adapted from my recall of the rainfall_Boris idea. I decided to include my friend CSY's shorter solution because contrasting these 2 solutions might provide valuable insight and help me remember some useful implementation/ECT techniques.
*/