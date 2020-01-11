#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
using Height=size_t;
using Idx=size_t;

template<  template<typename,class> class Container, 
typename V, class Alloc, int min_width=8>
std::ostream& operator<<(std::ostream& os, Container<V, Alloc> const& c){
   // takes any (container or otherwise) template having 2 templ params, but not maps (4) or sets (3)
   for(auto const & it : c){ os<<setw(min_width)<<it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}

/*first pass, try a rising line-up i.e. short,tall,short,tall
2nd pass, try a falling line-up, i.e. tall,short,tall,short

In each pass, shorten a tree to minimum (i.e. 1 meter) and move on
*/
size_t linearTime2pass(vector<Height> const & orig){
  vector<Height> arr=orig;
  cout<<arr;
  size_t ret=0;
  assert(arr.size() > 1);
  for (Idx i=1; i<arr.size(); ++i ){
    if (i%2==0) {
      cout<<"should rise to #"<<i<<"\n";
      if (arr[i-1] >= arr[i]){
        ++ret;
        arr[i]=1;
        cout<<i<<"'th tree shortened to minimum height\n";
      }
    }
  }
  //falling line-up
  cout<<arr<<" ^  beautified  ^\n";
  return 0;
}
int main(){
  linearTime2pass({7,5,2,3,6,4});
}/*Req: given a line-up of trees, the gardener wants them to look like short,tall,short,tall (or tall,short,tall,,). What's the minimum number of trees to shorten?

Each tree height is [2,1000], but if all the trees are initially 2m, then we can shorten some to 1m.
*/
