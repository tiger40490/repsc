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
/*
i is the starting point to scan;
prev is the pseudo-previous value to compare against arr[i]
*/
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
* aa: the level of arr[i-2] i.e. Ancestor
* bb: the level of arr[i-1] i.e. Before
* cc: the level of arr[i] i.e. Current
* dd: the level of arr[i+1] i.e. Descendent
*/
bool solABCD(vector<payload> const & arr){
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
    payload aa=INT_MIN;
    if (i>=2) aa =arr[i-2]; 
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
    if (bb < dd){ // bb or cc must disappear
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
// At the first roadblock, there are only two choice items we could kill. Try killing BB then try killing CC. We know right there if the array is fixable.
bool sol2kill(vector<payload> const & arr){
  cout<<"--- input arr ---\n"<<arr<<"\n";
  size_t sz = arr.size();
  if (sz <=2 ) return true;

  for (size_t i=1; i<sz; ++i){
    payload bb = arr[i-1], 
            cc = arr[i];
    if   ( bb < cc) continue;
    assert(bb >= cc);
    cout<<cc<<" #"<<i<<" <- offender found in sol2kill()\n";
    payload aa= (i>=2)? arr[i-2] : INT_MIN; 

    return isStrictlyRising(arr, aa, i) || // kill bb i.e. arr[i-1]
           isStrictlyRising(arr, bb, i+1); // kill cc
  }
  return true;
}
bool solFromBothEnds(vector<payload> const & arr){
  cout<<"--- input arr to solFromBothEnds() ---\n"<<arr<<"\n";
  size_t sz = arr.size();
  if (sz <=2 ) return true;

  for (int i=1; i<sz; ++i){
    payload bb = arr[i-1], 
            cc = arr[i];
    if   ( bb < cc) continue;
    assert(bb >= cc);
    cout<<cc<<" #"<<i<<" <- offender found in solFromBothEnds()\n";
    payload aa= (i-2>=0)? arr[i-2] : INT_MIN; 
	
    if (i == sz -1) return true; 
    payload dd=arr[i+1];
    if     (aa>=dd) return false; //immediate game over
    assert (aa< dd);
    bool isOK = (aa < bb && bb < dd)  // kill cc
		         || (aa < cc && cc < dd); // kill bb
    cout<<"aa="<<aa<<", bb="<<bb<<", cc="<<cc<<", dd="<<dd<<", isOK="<<isOK<<"\n";

    if (!isOK) return false;
    for (size_t j = i+1; j<sz-1; ++j){ //this loop can be seen as backscan to dd or forward scan from dd
      if (arr[j] >= arr[j+1]) return false;
    }
	//cout<<"end of backscan. returning true\n"; return true;
  }
  return true;
}
bool solAshS(vector<int> arr) {
  cout<<"--- input arr to solAshS() ---\n"<<arr<<"\n";
  size_t sz = arr.size();
  if (sz <= 2) return true;
  bool isIntact = true; // no removal yet
  for (size_t i = 0; i < (sz - 1); i++) { //bb go from 0th to 2nd last
    int bb=arr[i], cc=arr[i + 1];
    if (bb >= cc) {
      if (!isIntact){
        cout<<i<<" = i (bb) when we found a 2nd offender :(\n";
        return false;
      }
      isIntact = false;
      
      int aa = i==0? INT16_MIN : arr[i - 1]; //aa
      if (i + 2 > sz -1) return true;
      int dd = arr[i + 2]; //dd
      bool isOK=!(aa >= cc && bb >= dd);
      cout<<"aa="<<aa<<", bb="<<bb<<", cc="<<cc<<", dd="<<dd<<", isOK="<<isOK<<"\n";

      if (!isOK) {
      // aa >= cc && bb >= dd so both bb and cc must go
      // This aa/bb/cc/dd section is beyond repair
        return false;
      }//else continue the loop, but which element to kill?
    }
  }
  return true;
}
bool almostIncreasingSequence(vector<payload> const & arr){
  //return solAshS(arr);
	
	// test all 4 solutions:
  bool   ret  = solABCD(arr);
  assert (ret == sol2kill(arr));
  assert (ret == solAshS(arr));
  assert (ret == solFromBothEnds(arr));
  return ret;
}
int main(){
  assert (! almostIncreasingSequence({2,3,1,2})); 
  assert ( almostIncreasingSequence({1,2,3,4,3,6})); 
  assert ( almostIncreasingSequence({10,1,2,3,4})); 
  assert ( almostIncreasingSequence({10,11,12,13,14})); 
  assert (! almostIncreasingSequence({1,2,3,4,5,3,5,6})); 
  assert ( almostIncreasingSequence({11,22,18,22,33})); 
  assert (! almostIncreasingSequence({1,2,1,2})); 
  assert ( almostIncreasingSequence({1,2,5,3,5})); 
  assert (! almostIncreasingSequence({40,50,60,10,20,30})); 
  assert ( almostIncreasingSequence({1,2,3,4, 99 ,5,6,7,8})); 
  assert ( almostIncreasingSequence({1,2,3,4,5, 15}));
  assert ( almostIncreasingSequence({15,6}));
  assert ( almostIncreasingSequence({4,6,4}));
  assert (! almostIncreasingSequence({1,2,3,  4,4, 15,6}));
  assert (! almostIncreasingSequence({4,4,4}));
}
/*Requirmenet (from GrassHopper Nov 2020): given an int array (size < 100000), can you make the array strictly increasing by removing at most one elmeent?
 */
