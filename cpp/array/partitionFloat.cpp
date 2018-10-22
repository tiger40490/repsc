//showcase: std::swap on 2 vector element2
//todo: blog to reference this github file
//todo: more tests
//todo: return -1....
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
   os<<"----"<<endl;
   return os;
}
vector<int> arr;
//return index of first element that exceeds pivot, or -1 if pivot too high
int partition(int const pivotVal, idx le, idx ri){
  int const & p = pivotVal;
  cout<<arr;
  while(1){ //invariant: arr[le-1] <= p and arr[ri+1] > p
    for (; arr[le] <= p; ++le){
      if (le == ri) return ri;
    }assert(arr[le] > p);
    
    for (; arr[ri] >  p; --ri){
      if (le == ri) return le; //see arr[le] assert above
    }assert(arr[le] > p);
    
    cout<<arr<<" <- before swapping "<<le<<" / "<<ri<<endl;
    assert(le<ri);
    std::swap(arr[le], arr[ri]);
    cout<<arr<<" <- after swapping \n"<<endl;
    //cout<<le<<" = le; ri = "<<ri<<endl;
    if (le == ri-1) return ri;
    ++le;
    --ri;
  }
}
void test1(int const pivotVal, vector<int> v){
  arr=v;
  auto ret = partition(pivotVal, 0, v.size()-1);
  cout<<"ret = "<<ret<<endl<<arr;
}
int main(){
  test1(5.1, {7,1,9,9,5,4,9,5,7});
}/*Req: partition an int array using a float pivot value*/