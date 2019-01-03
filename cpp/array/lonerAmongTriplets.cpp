/*
showcase: 
*/
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned int idx;
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<"---- ";
   return os;
}
vector<int> arr; //global var
/* return index of first element that exceeds pivot
* Only one swap for each wrong pair. (I used to think 2 swaps required on each "occasion"
*/
int partitionFwd(int const pivotVal, idx le, idx const ri){
  int const & p = pivotVal;
  cout<<arr<<le<<" = le; ri = "<<ri<<endl;
  for (;;++le){
    if (le == ri) {
      cout<<"pivot too high :( \n";
      return -1; //pivotVal skyhigh
    }
    if (arr[le] > p) {
      //cout<<arr<<le <<" <-- back ptr initialized.. Now scan fwd from there..."<<endl;
  	  break;
	  }
  }
  for (idx front=le+1; front <= ri; ++front){
    if (arr[front] > p) continue;
    swap(arr[le], arr[front]);
    ++le;
    assert(arr[le] > p);
  }
  cout<<arr<<le<<" = ret from partitionFwd\n";
  return le; //index of first element exceeding p
}
int wrapper(vector<int> v){
  arr=v;
  cout<<"  --- v -- v --- \n"<<v<<endl;
  auto sz = v.size();
  assert(sz > 3);
  assert(sz % 3 == 1);
  int ret = 0, le=0, ri=sz-1;
  for(; ri-le>1;){
    ret = partitionFwd(v[le], le, ri);
    //break; //just for now
    if (ret % 3){ //discard right segment
      ri=ret-1;
    }else{ //discard left segment eg: 0 1 2 ret=3
      le=ret;
    }
  }
  //assert(le==ri);
  ret = arr[le];
  cout<<ret<<" = ret\n\n";
  arr=v; //for subsequent test
  return 1; //harded for now
}
int main(){
  assert(1 == wrapper({4,2,2,4,2,4,7,7,7,5,5,5,3,3,3,8,8,8,6,6,6,1}));
}/*Req: Given array of integers, every element appears three times except for one, which appears exactly once. Find that single one in a linear runtime. Could you implement it without using extra memory?
*/