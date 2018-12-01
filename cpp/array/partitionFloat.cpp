//showcase: std::swap on 2 vector elements
/*todo: impplement 2-pivot partition based on the fwd scanning. p1, p2 are the 2 pivot values. 
invariant: left and right ptr both at "first" item strictly between p1 and p2.
I hope to use fewer than 4 moving pointers. How about a 3rd ptr scanning forward, until it meets the right ptr?
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
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<"---- ";
   return os;
}
vector<int> arr; //global var
/* for both partition algos:
* return index of first element that exceeds pivot, or -1 if pivot too high
* Only one swap for each wrong pair. (I used to think 2 swaps required on each "occasion"
*/
int partitionFwd(float const pivotVal, idx le, idx const ri){
  float const & p = pivotVal;
  for (;;++le){
    if (le == ri) return -1; //pivotVal skyhigh
    if (arr[le] > p) {
      cout<<arr<<le <<" <-- back ptr initialized.. Now scan fwd from there..."<<endl;
  	  break;
	  }
  }
  for (idx front=le+1; front <= ri; ++front){
    if (arr[front] > p) continue;
    swap(arr[le], arr[front]);
    ++le;
    assert(arr[le] > p);
  }
  return le; //index of first element exceeding p
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
int wrapper(float const pivotVal, vector<int> v, idx le=0, idx ri=0){
  arr=v;
  if (ri==0) ri = v.size()-1;
  cout<<"  --- v -- v -- \n"<<arr<<"pivotVal = "<<pivotVal<<" , le = "<<le<<" , ri = "<<ri<<endl;
  auto ret = partition2oppScanner(pivotVal, le, ri);
  assert(ret == partitionFwd(pivotVal, le, ri));
  cout<<arr<<ret<<" = ret from both algos\n\n";
  return ret;
}
int main(){
  assert(8 == wrapper(3.3, {8,12,7,1,2,-7,5,-3,0,3,9,-6,4,9,2,6,9,5}));
  assert(6 == wrapper(5.2, {7,4,1,9,9,5,4,9,5,7,11}, 1,8));
  assert(-1== wrapper(15.1, {7,1,9,9,5,4,9,5,7}));
  assert(6 == wrapper(5.1, {4,3,7,1,9,9,5,4,9,5,7}));
  assert(4 == wrapper(5, {7,1,9,9,5,4,9,5,7}));
  assert(-1 == wrapper(5, {5,5,5,5,5,5}));
  assert(0 == wrapper(5, {6,6,6,6}));
}/*Req: partition an int array using a float (can be an integer) pivot value

i feel this challenge is more practical than most Leetcode problems.
*/
