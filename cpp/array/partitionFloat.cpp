/*
todo: what if p1==p2?
todo: what if p1 == min
todo: what if p2 == max

showcase: const-ref-vector parameter can receive an init-list, but const is needed. A temp object is probably created on the stack.
showcase: std::swap, by-reference, 2 vector elements .. by reference!
showcase: c++11 typedef for pair<int,int> then calling its default ctor
min/max_element() are O(N) but don't aggrivate the time complexity
*/
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
using idx = unsigned int;
using pi2 = pair<idx,idx>;
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<"-- ";
   return os;
}
vector<int> arr; //global var
/* partition a given array using 2 pivot values. return two subscripts -- first items exceeding P1/P2

O(N): main loop iterates exactly N times because each iteration we increment either front or ri pointer
*/
pi2 partition2(float const & pivotVal1, float const & pivotVal2){
  auto const origArr(arr);
  float const & p1=pivotVal1, & p2=pivotVal2;
  auto minItr = min_element(arr.begin(), arr.end());
  auto maxItr = max_element(arr.begin(), arr.end());
  cout<<"    ~ ~ ~ ~\n"<<arr<<p1<<" = p1; p2 = "<<p2<<" ... "<<*minItr<<" = min; max = "<<*maxItr<<endl;
  assert(p1<= p2); // no point validating input..not a programming challenge
  assert(p1 < *maxItr && "first pivot value too high");
  idx le=0, ri=arr.size()-1;
  for (;;++le){
    if (arr[le] >  p1) break;
    assert(le != ri);
  }
  for (;;--ri){ //must skip all > p2
    if (arr[ri] <= p2) break;
    assert(le != ri);
  }
  cout<<arr<<le <<" <- left/right ptr initialized -> "<<ri<<" #leftward first item =< p2"<<endl;
  for (idx front=le+1; front <= ri; ){
    if (arr[front] > p1){
        if (arr[front] <= p2) {
          ++front;
          continue; 
        }
        //cout<<ri<<" swapping (right end) with "<<front<<endl;
        swap(arr[front], arr[ri]);
        ///cout<<arr<<le<<'{'<<front<<'}'<<ri<<endl;
        --ri;
        assert(arr[ri+1]>p2 && "invariant: if valid, ri+1 is the leftward first > p2; ri item is unknown");
        // now front (also ri) item may be too high or too low, so we can't increment front pointer yet
    }else{
        assert (arr[front] <= p1);
    //if (1) {
        assert (arr[le] > p1);
        cout<<le<<" swapping (left end) with "<<front<<endl;
        swap(arr[le], arr[front]);
        ++le; // still behind front
        cout<<arr<<le<<'{'<<front<<'}'<<ri<<endl;
        assert(le<=front);
        assert(arr[le] > p1);
        ++front;
    }
  }// main loop 
  assert(ri+1 <= arr.size()-1);
  cout<<arr<<le<<" (=ret=) "<<ri+1<<endl;
  arr = origArr;
  return pi2(le, ri+1);
}
//////////////////
using pii = pair<int,size_t>;
/* return index of first element exceeding pivot, or -1 if pivot too high
2nd returned value is number of elements equal to pivot

This algo is short (ignoring asserts) but intense and tiring on the mind due to large number (about 3) of stateful variables and many (about 5) corner cases
*/
pii partitionFwdLinearTime(float const & pivotVal, idx const & le, idx const & ri){
  float const & p = pivotVal; //abbr alias
  idx back = le;
  
  for (;;++back){
    if (arr[back] >= p) break;
    if (back == ri) return {-1,0}; //pivotVal higher than any item
  }
  size_t frq = (arr[back]==p); //frq of pivotVal occurence
  cout<<arr<<" pivotVal = "<<p<<"; frq = "<<frq<<"; "<<back <<" <-- back ptr initialized to first item >= pivot .. Now scan fwd from there..."<<endl;
  
  for (idx front=back+1; front <= ri; ++front){
    auto & cur = arr[front]; //reference needed for std::swap
    if (cur > p) continue;
    auto & bey = arr[back+frq]; //beyond all items =< p
    if (cur == p){
      if (back+frq == front) {
        ++frq;    
        continue;
      }
      //cout<<arr<<back<<" = back; =b4=.. frq = "<<frq<<"; front = "<<front<<endl;
      assert(back+frq < front);
      assert(bey >= p);
      assert(back+frq == 0 || arr[back+frq-1] <= p);
      swap(bey, cur); //!
      ++frq;
      //cout<<arr<<back<<" = back; =af=.. frq = "<<frq<<endl;
      assert(arr[front] >= p); //post condition
      continue;
    }else{ //cur too low
      if (bey != cur) swap(bey, cur); //might refer to the same item
      assert(bey < p);
      swap(bey, arr[back]);
      ++back;
      assert(arr[back] >= p);
      assert(arr[back-1] <p);
    }
  }
  if (arr[ri] <= p) return {-1, frq};
  cout<<back<<" = back (returning); frq = "<<frq<<endl;
  return {back+frq, frq}; //index of first element exceeding p
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
pii wrapper(float const pivotVal, vector<int> const & v, idx le=0, idx ri=0){
  arr=v;
  if (ri==0) ri = v.size()-1;
  cout<<"  --- v -- v -- \n"<<arr<<"pivotVal = "<<pivotVal<<" , le = "<<le<<" , ri = "<<ri<<endl;
  auto ret = partitionFwdLinearTime(pivotVal, le, ri);
  assert(ret.first == partition2oppScanner(pivotVal, le, ri));
  cout<<arr<<ret.first<<" = ret from both algos\n\n";
  arr=v; //for subsequent test
  return ret;
}
int main(){
  assert(pii({1,0}) == wrapper(5, {6,2}));
  assert(pii({3,3}) == wrapper(5, {6,5,5,5}));
  assert(pii({-1,1}) == wrapper(5, {2,2,5}));
  assert(pii({-1,6}) == wrapper(5, {5,5,5,5,5,5}));
  assert(pii({-1,1}) == wrapper(19, {7,1,19,9,5,4}));
  assert(pii({4,2}) == wrapper(5, {7,1,9,9,5,4,9,5,7}));
  assert(pii({6,0}) == wrapper(5.2, {7,4,1,9,9,5,4,9,5,7,11}, 1,8));
  assert(pii({-1,0}) == wrapper(15.1, {7,1,9,9,5,4,9,5,7}));
  assert(pii({6,0}) == wrapper(5.1, {4,3,7,1,9,9,5,4,9,5,7}));
  assert(pii({0,0}) == wrapper(5, {6,6,6,6}));
  //testing 2-pivot partitioning
  assert(pii({8,0}) == wrapper(3.3, {4,-2,12,7,1,-7,5,-3,0,3,9,-6,4,8,2,6,9,5}));
  assert(pi2(7,10) == partition2(2.2, 4.4));
  assert(pi2(7,14) == partition2(2.2, 7.7));
}/*Req: partition an int array using a float pivot value, and return the count of items equal to pivot value

i feel this challenge is more practical than most Leetcode problems.
*/
