/* 
 */
#include <vector>
#include<climits>
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

typedef int payload;
bool isStrictlyRising(vector<payload> const & v, payload prev, size_t i=1){
  cout<<i<<"=i, prev="<<prev<<"  entering isStrictlyRising()...\n";
  size_t const lastPos = v.size()-1;
  if ( i == lastPos) return prev < v[i]; 
  if (i >= lastPos) return true; 
  for (; i<v.size(); ++i){
    //cout<<v[i]<<" being checked against "<<prev<<" ...\n";
    if (prev >= v[i]) {
      cout << v[i]<<" #"<<i<<" <- offender found in isStrictlyRising()\n";
      return false;
    }
    prev = v[i];
  }
  return true;
}
/* When we hit an offender at position i, we will have three benchmarks
* A: the level of arr[i-2] i.e. Ancestor
* B: the level of arr[i-1] i.e. Before
* C: the level of arr[i] i.e. Current
*/
bool almostIncreasingSequence(vector<payload> const & arr){
  cout<<"--- input arr ---\n"<<arr<<"\n";
  size_t sz = arr.size(), lastPos = sz-1;
  if (sz <=2 ) return true;
  bool ret=true;
  if (arr[0] >= arr[1]){// first element must disappear
    ret = isStrictlyRising(arr, INT_MIN, 1);
    cout<<ret<<" .. returned due to isStrictlyRising() # case 0 \n";
    return ret;
  }
  for (size_t i=1; i<sz; ++i){
    payload bb = arr[i-1], cc = arr[i];
    if (bb < cc) continue;
    assert (bb >= cc);
    cout<<cc<<" #"<<i<<" <- offender found in almostIncreasingSequence\n";
    size_t aa=arr[i-2]; // what if neg?
    if (aa >= cc){ // cc must disappear
      ret = isStrictlyRising(arr, bb, i+1);
      cout<<ret<<" .. returned due to isStrictlyRising() # case C1 \n";
      return ret;
    }
    assert (aa < cc);
    if (i == lastPos){
      return true; // bb or cc can disappear
    }
    payload dd = arr[i+1];
    if (cc >= dd){
      return false; //two non-rising nodes in a row
    }
    if (bb < dd){ // cc must disappear
      ret = isStrictlyRising(arr, bb, i+1);
      cout<<ret<<" .. returned due to isStrictlyRising() # case C2 \n";
      return ret;
    }
    //what if bb == dd > cc? bb must go
    assert (bb >= cc);
    assert (aa < cc); // same assert again
    assert (cc < dd); 
    assert (bb >= dd);
    // bb must disappear
    ret = isStrictlyRising(arr, cc, i+1);
    cout<<ret<<" .. returned due to isStrictlyRising() # case B \n";
    return ret;
  }
  return true;
}
int main(){
  assert ( almostIncreasingSequence({10,11,12,13,14})); 
  assert ( almostIncreasingSequence({11,22,18,22,33})); 
  assert ( almostIncreasingSequence({10,1,2,3,4})); 
  assert (! almostIncreasingSequence({1,2,3,4,5,3,5,6})); 
  assert (! almostIncreasingSequence({1,2,1,2})); 
  assert ( almostIncreasingSequence({1,2,5,3,5})); 
  assert (! almostIncreasingSequence({40,50,60,10,20,30})); 
  assert ( almostIncreasingSequence({1,2,3,4,99,5,6,7,8})); 
  assert ( almostIncreasingSequence({1,2,3,4,5, 15}));
  assert ( almostIncreasingSequence({15,6}));
  assert ( almostIncreasingSequence({4,6,4}));
  assert (! almostIncreasingSequence({1,2,3,4,4, 15,6}));
  assert (! almostIncreasingSequence({4,4,4}));
}
/*Requirmenet (from GrassHopper Nov 2020): given an int array (size < 100000), can you make the array strictly increasing by removing at most one elmeent?
 */
