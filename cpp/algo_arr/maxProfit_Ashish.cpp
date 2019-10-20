#include <vector>
#include <iostream>
#include <iomanip>
#include <assert.h>
#define ss if(2>1) cout
using namespace std;

template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   os<<"val ";
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<"\nidx";
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
int sol2(vector<int> arr){
  cout<<arr;
  if (arr.size() <= 1) return 0;  //short arrays
  
  int lwm=arr[0], maxP=0;
  for (size_t i=0; i<arr.size(); ++i){
    int cur=arr[i];
    if (cur < lwm) {
  	  lwm = cur;
    }else{
 	  int diff = cur - lwm;
	  if (diff > maxP) maxP = diff;
    }
  }
  cout<<maxP<<" is max profit\n";
  return maxP;
}
int main(){
  assert( 8  == sol2({1,2,4,2,5,7,2,4,9,0}));
  assert( 12 == sol2({1,2,0,12,5,2,4,8,0}));
  assert( 0  == sol2({7,2}));
  assert( 5  == sol2({5,10,8,7,6,5}));
}