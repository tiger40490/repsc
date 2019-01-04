/*
todo: fix wrapper to return a pair and assert on both
showcase: std::swap on 2 vector elements by reference
showcase: c++11 typedef for pair<int,int> then calling its default ctor
todo: implement 2-pivot partition based on the fwd scanning. p1, p2 are the 2 pivot values. 
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
   os<<"-- ";
   return os;
}
vector<int> arr; //global var
/* partition a given array using 2 pivot values. 
returns 2 indices 
*/
using pii = pair<int,int>;
pii partition2(float const pivotVal1, float const pivotVal2){
  float const p1=pivotVal1, p2=pivotVal2;
  auto minItr = min_element(arr.begin(), arr.end());
  auto maxItr = max_element(arr.begin(), arr.end());
  cout<<arr<<p1<<" = p1; p2 = "<<p2<<" ... "<<*minItr<<" = min; max = "<<*maxItr<<endl;
  assert(p1<=p2); // no point validating input..not a programming challenge
  assert(*minItr <= p1 && "1st pivot value too low");
  assert(p2 <= *maxItr && "2nd pivot value too high");
  idx le=0;
  idx const ri=arr.size()-1;
  for (;;++le){
    assert(le != ri);
    if (arr[le] > p1) 	  break;
  }
  cout<<arr<<le <<" <-- back ptr initialized.. Now scan fwd from there..."<<endl;
  for (idx front=le+1; front <= ri; ++front){
    if (arr[front] > p1) continue;
    swap(arr[le], arr[front]);
    ++le;
    assert(arr[le] > p1);
  }
  idx const ret1 = le;
  cout<<arr<<ret1<<" <- first partition\n";
  
  for (;;++le){
    assert(le != ri);
    if (arr[le] > p2) 	  break;
  }
  cout<<arr<<le <<" <-- 2nd back ptr initialized.. Now scan fwd from there..."<<endl;
  for (idx front=le+1; front <= ri; ++front){
    if (arr[front] > p2) continue;
    swap(arr[le], arr[front]);
    ++le;
    assert(arr[le] > p2);
  }
  cout<<arr<<le<<" <- 2nd partition\n";
  return pii(ret1, le);
#ifdef oldAbandonedSol
//invariant: left and right ptr both at "first" item strictly between p1 and p2. 
//I hope to use fewer than 4 moving pointers. How about a 3rd ptr scanning forward, until it meets the right ptr?
  idx le=0, ri=arr.size()-1;
  for (;;){
    assert(le != ri);
    if (p1 < arr[le]) {
      if (   arr[le] < p2)  	    break;
      swap(arr[le], arr[ri]); //le item too high
      --ri;
	  }else{
      ++le;
    }
  }
  assert(p1 < arr[le]);
  assert(arr[ri] > p2);
  cout<<arr<<le<<" < - > "<<ri <<" <-- both ptr initialized.. Now scan fwd from le..."<<endl;
#endif
}
/* return index of first element exceeding pivot, or -1 if pivot too high
2nd returned value is number of elements equal to pivot
* Only one swap for each wrong pair. (I used to think 2 swaps required on each "occasion"
*/
pii partitionFwd(float const pivotVal, idx le, idx const ri){
  float const & p = pivotVal;
  
  for (;;++le){
    if (le == ri) return {-1,0}; //pivotVal skyhigh
    if (arr[le] >= p) {
      cout<<arr <<" pivotVal = "<<p<<";"<<le <<" <-- back ptr initialized to first item >= pivot .. Now scan fwd from there..."<<endl;
  	  break;
	  }
  }
  size_t frq = (arr[le]==p)?1:0;
  for (idx front=le+1; front <= ri; ++front){
    auto & cur = arr[front];
    if (cur > p) continue;//ok
    if (cur == p){
      cout<<arr<<le<<" = le; =b4=.. frq = "<<frq<<"; front = "<<front<<endl;
      auto & kk = arr[le+frq];
      assert(kk > p);
      assert(arr[le+frq-1] <= p);
      swap(kk, cur);
      ++frq;
      cout<<arr<<le<<" = le; =af=.. frq = "<<frq<<endl;
      
      assert(arr[front] > p); //post condition
    }else{ //cur too small
      swap(arr[le+frq], cur);
      swap(arr[le+frq], arr[le]);
      
      ++le;
      assert(arr[le] >= p);
      assert(arr[le-1] <p);
    }
  }
  if (arr[ri] <= p) return {-1, frq};
  cout<<le<<" = le (returning); frq = "<<frq<<endl;
  return {le+frq, frq}; //index of first element exceeding p
}
/*different from familiar qsort partition algo. Too complicated in implementation. Not worth memorizing.
*/
int partition2oppScanner(float const pivotVal, idx le, idx ri){
  float const & p = pivotVal;
  while(1){ //invariant: arr[le-1] <= p and arr[ri+1] > p
    for (; arr[le] <= p; ++le){
      if (le == ri) { //exit condition
    		//cout<<arr<<le <<" == le == ri... exiting \n";
        if (ri == arr.size()-1) return -1;
        return le+1;
      }
    }assert(arr[le] > p);
    
    for (; arr[ri] >  p; --ri){
      if (le == ri) return le; //see arr[le] assert above
    }assert(arr[ri] <= p);
    
    cout<<arr<<" <- before swapping two elements "<<le<<" / "<<ri<<endl;
    assert(le<ri);
    std::swap(arr[le], arr[ri]);
    cout<<arr<<" <- after swapping \n"<<endl;
    //cout<<le<<" = le; ri = "<<ri<<endl;
    if (le == ri-1) return ri;
    ++le;
    --ri;
  }
}
pii wrapper(float const pivotVal, vector<int> v, idx le=0, idx ri=0){
  arr=v;
  if (ri==0) ri = v.size()-1;
  cout<<"  --- v -- v -- \n"<<arr<<"pivotVal = "<<pivotVal<<" , le = "<<le<<" , ri = "<<ri<<endl;
  auto ret = partitionFwd(pivotVal, le, ri);
  assert(ret.first == partition2oppScanner(pivotVal, le, ri));
  cout<<arr<<ret.first<<" = ret from both algos\n\n";
  arr=v; //for subsequent test
  return ret;
}
int main(){
  assert(pii({-1,1}) == wrapper(19, {7,1,19,9,5,4}));
  assert(pii({4,2}) == wrapper(5, {7,1,9,9,5,4,9,5,7}));
  assert(pii({8,0}) == wrapper(3.3, {4,-2,12,7,1,-7,5,-3,0,3,9,-6,4,8,2,6,9,5}));
  assert(pii({6,0}) == wrapper(5.2, {7,4,1,9,9,5,4,9,5,7,11}, 1,8));
  assert(pii({-1,0}) == wrapper(15.1, {7,1,9,9,5,4,9,5,7}));
  assert(pii({6,0}) == wrapper(5.1, {4,3,7,1,9,9,5,4,9,5,7}));
  assert(pii({0,0}) == wrapper(5, {6,6,6,6}));
#ifdef aaa  
  assert(pii({-1,6}) == wrapper(5, {5,5,5,5,5,5}));
  assert(pii(7,14) == partition2(2.2, 7.7));
#endif 
}/*Req: partition an int array using a float (can be an integer) pivot value

i feel this challenge is more practical than most Leetcode problems.
*/
