#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;
template<typename K, typename V> ostream & operator<<(ostream & os, pair<K,V> const & p){
   os<<p.first<<":"<<p.second;
   return os;
}
template<typename K, typename V, int min_width=4> ostream & operator<<(ostream & os,  map<K,V> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
typedef int Level; // can be negative
int solution(vector<int> &A) {
    size_t N = A.size(); ss<<N<<" = N\n";
    map<Level, size_t> frq;
    for(Level const & i: A) frq[i]++;
    ss<<frq;
    if (frq.size()==1) return N; //original sequence's length
    size_t ret=1;	
    for(auto it=frq.begin(); it!=frq.end(); ++it){
      /*a "band" consists of 2 adjacent levels like levels 6/7, or 3/4 but not 3/5. 
      We scan from lowest band to highest band, and count how many elements are in each band*/
	  Level const & b=it->first;
      ss<<b<<" is the lower value of current band\n";
	  auto const cnt = it->second + (frq.count(b+1)? frq[b+1]:0);
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
    assert(3==sol({6, 100, 6, 90, 7, 8}));
    assert(7==sol({6,6,6,  6,6,6,6}));
}
