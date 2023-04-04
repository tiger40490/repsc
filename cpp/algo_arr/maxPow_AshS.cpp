/* 
 */
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <assert.h>
using namespace std;
template<  template<typename,class> class Container, 
typename V, class Alloc, int min_width=8>
std::ostream& operator<<(std::ostream& os, Container<V, Alloc> const& c){
   // takes any (container or otherwise) template having 2 templ params, but not maps (4) or sets (3)
   for(auto const & it : c){ os<<setw(min_width)<<it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   //os<<endl;
   return os;
}
typedef int num_t; 
typedef size_t pos_t; //index into the num_t array

/* A more efficient version of this function will use the last 3 params to remember previous calculations and avoid revisiting the middle elements of arr.
*/
num_t sliceSum(pos_t L, pos_t R, vector<num_t> const & arr, 
  num_t previousSubArraySum, pos_t previousLeftEnd, pos_t previousRightEnd){
  num_t ret=0;
  cout<<previousLeftEnd<<" = previousLeftEnd; previousRightEnd = "<<previousRightEnd<<endl;
  
  for (pos_t i = L; i<=R; ++i){
    ret += arr[i];
  }
  cout<<ret<<" returned from sliceSum() ^^^^^^^^^^^^^^^^^^ \n";
  return ret;
}
num_t solution(vector<num_t> const & arr, vector<pos_t> const & _indices){
  vector<pos_t> p=_indices; sort(p.begin(), p.end());
  size_t const K = p.size();
  num_t thePower = 0, lastSliceSum=0;
  for (size_t j=K/2; j<K; ++j){
    size_t i = K-j-1;
    cout<<p[i]<<" <- i; j -> "<<p[j]<<endl;
    lastSliceSum = sliceSum(p[i], p[j], arr, lastSliceSum, p[i+1] ,p[j-1]);
    thePower += lastSliceSum;
  }
  return thePower;
}
int main(){
  assert(25==solution({3,5,6,0,7}, {3,1,0,2}) );
  assert(39==solution({3,5,6,0,7}, {3,1,0,2,3,0}) );
}
/*Requirmenet: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=44635&action=edit
 */
