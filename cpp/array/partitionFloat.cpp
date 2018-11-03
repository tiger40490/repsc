//showcase: std::swap on 2 vector elements
//todo: more tests
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
vector<int> arr;
/*different from std qsort partition algo
return index of first element that exceeds pivot, or -1 if pivot too high
*/
int partition2oppScanner(float const pivotVal, idx le, idx ri){
  float const & p = pivotVal;
  cout<<arr<<"pivotVal = "<<p<<endl;
  while(1){ //invariant: arr[le-1] <= p and arr[ri+1] > p
    for (; arr[le] <= p; ++le){
      if (le == ri) {
        if (ri == arr.size()-1) return -1;
        return ri;
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
int wrapper(float const pivotVal, vector<int> v){
  arr=v;
  auto ret = partition2oppScanner(pivotVal, 0, v.size()-1);
  cout<<arr<<ret<<" = ret\n\n";
  return ret;
}
int main(){
  assert(-1== wrapper(15.1, {7,1,9,9,5,4,9,5,7}));
  assert(4 == wrapper(5.1, {7,1,9,9,5,4,9,5,7}));
  assert(4 == wrapper(5, {7,1,9,9,5,4,9,5,7}));
  assert(-1 == wrapper(5, {5,5,5,5,5,5}));
  assert(0 == wrapper(5, {6,6,6,6}));
}/*Req: partition an int array using a float (can be an integer) pivot value*/
