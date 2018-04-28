#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;
template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
typedef int ts; //timestamp;
typedef int Position; //0 to N, N being the destination
typedef int Gap; //between 0 and 2, gap is 2
size_t N=0;
//in the vector param, true at 0th position means stone visible there
bool isGood(vector<bool> const & visible, int const D){
  assert(visible.size() == N+1);
  ss<<"visible = "<<visible;
  Gap gap=0; Position lastStone = -1;
  for(size_t i=0; i<visible.size(); ++i){
    if (visible[i]){ gap = 0; lastStone=i;
    }else{
        gap++;
        if (gap >= D) { ss<<lastStone<<'~'<<i<<" is equal to D="<<D<<", too far apart :(\n";
          return false;
        }
    }
  } return true;
}
int solution(vector<int> &A, int D) {
    N = A.size(); ss<<N<<" = dest position\n";
    if (D >= (int)(1+N)) return 0;//N+1 gaps apart,single jump of size(N+1)will do

    //Play the movie of stones at time 0, time 1, time 2...
    //check isGood() at each snapshot. If good, return the timestamp.
    //if still no good at end of the movie, then return -1
    set<ts> const times(A.begin(), A.end());
    for(auto it =times.begin(); it!=times.end(); ++it){
      ts const t=*it;
      if (t<0) continue;
      ss<<t<<" = timestamp\n";
      vector<bool> vis(N);
      for(Position p=0; p<N; ++p) vis[p] = A[p] <= t && A[p]!=-1;
      vis.push_back(true); //pretend destination is a visible stone
      if (isGood(vis, D)) return t;
    }
    return -1;
}
int sol(vector<ts> A, int D){
    auto ret = solution(A, D);
    ss<<ret<<" <----- returned\n";
    return ret;
}
int main(){
    //cout<<isGood({false, false, true,false,false, false}, 2);
    assert(6==sol({1, 7,-1,6, 0, 2, 8,3, 5}, 3));
    assert(2==sol({1, -1, 0, 2, 3, 5}, 3));
    assert(3==sol({3, 2, 1}, 1));
    assert(-1==sol({5, 2, -1, 4, -1, -1, -1}, 3));
}
//Requirement: https://bintanvictor.wordpress.com/2018/04/28/monkey-crossing-river-codility/
