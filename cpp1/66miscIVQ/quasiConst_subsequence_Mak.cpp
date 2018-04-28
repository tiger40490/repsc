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
typedef int Level; // can be negative
int solution(vector<int> &A) {
    size_t N = A.size(); ss<<N<<" = N\n";
    ss<<A;
    Level lowest = *min_element(A.begin(), A.end());
    Level highest = *max_element(A.begin(), A.end());
    ss<<lowest<<"~"<<highest<<endl;
    if (lowest == highest) return N; //original sequence's length
    size_t ret=1;
    for(Level b=lowest; b<=highest-1; ++b){
      ss<<b<<" is the lower value of current band\n";
      /*a "band" consists of 2 adjacent levels like levels 6/7, or 3/4 but not 3/5. 
      We scan from lowest band to highest band, and count how many elements are in each band*/
      size_t cnt=0;
      for(unsigned int i=0; i<N; ++i){
        cnt +=  (A[i]==b || A[i]==b+1);
      }
      ss<<cnt<<" = cnt\n";
      if (ret < cnt) ret = cnt;
    }
    return ret;
}
int sol(vector<int> A){
    ss<<A;
    auto ret = solution(A);
    ss<<ret<<" returned\n";
    return ret;
}
int main(){
    assert(3==sol({6, 10, 6, 9, 7, 8}));
    assert(7==sol({6,6,6,  6,6,6,6}));
}
