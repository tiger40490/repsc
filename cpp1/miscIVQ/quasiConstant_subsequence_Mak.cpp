#include <vector>
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
typedef int Level;
size_t N=0;
int solution(vector<int> &A) {
    N = A.size(); ss<<N<<" = N\n";
    ss<<A;
    //a band has 2 adjacent levels like 6~7
    auto lowest = *min_element(A.begin(), A.end());
    auto highest = *max_element(A.begin(), A.end());
    ss<<lowest<<"~"<<highest<<endl;
    size_t ret=1;
    for(Level b=lowest; b<highest; ++b){
      ss<<b<<" is the lower value of current band\n";
      //scan from lowest band and count how many elements are in this band
      size_t cnt=0;
      for(unsigned int i=0; i<N; ++i){
        auto v = A[i];
        cnt +=  (v==b || v==b+1);
      }
      ss<<cnt<<" = cnt\n";
      if (ret < cnt) ret = cnt;
    }
    return ret;
}
int sol(vector<int> A){
    ss<<A;
    return solution(A);
}
int main(){
    ss<<sol({6, 10, 6, 9, 7, 8})<<" returned\n";
}
