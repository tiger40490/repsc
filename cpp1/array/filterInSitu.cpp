//showcase type alias
//showcase stable_sort. Actually std::sort happens to be stable in this case
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;
using ele=int;
bool isBad(ele const & item){return item < 0;}
bool isGood(ele const & item){return !isBad(item);}
bool comp(ele const & a, ele const & b){ return isBad(a)<isBad(b); }
void dump(vector<ele> const & arr){
  for(auto & e: arr) cout<<e<<" ";
  cout<<"  size = "<<arr.size()<<endl;
}
void swp(vector<ele> & arr, size_t le, size_t ri){
  auto tmp = arr[le];
  arr[le] = arr[ri];
  arr[ri] = tmp;
}
void solution3(vector<ele> & arr){//scan from both ends inward
  int le=0, ri=arr.size()-1;
  for(;le<=ri;){
    if (isGood(arr[le])){
	  ++le;
	  continue;
	}
    if (isBad(arr[ri])){
	  --ri;
	  continue;
	}
	swp(arr, le,ri);
  }
  arr.resize(le);
  dump(arr);
}
void solution2(vector<ele> & arr){//by stable_sort
  stable_sort(arr.begin(), arr.end(), comp);
  dump(arr);
  //binary search for the first bad then resize the vector to discard all bad
}
void solution4Victor(vector<ele> & arr){
  auto nextBad=arr.begin(); //next good
  auto nextGood=arr.begin(); //next bad
  for(;;){
    nextBad = find_if(nextBad+1, arr.end(), isBad);
    if (nextBad == arr.end()) {
	    cout<<"no bad anywhere\n";
    	break;
	}
	nextGood =find_if(max(nextBad+1, nextGood), arr.end(), isGood);
    if (nextGood == arr.end()) {
	    cout<<"no more good\n";
    	break;
	}
	swap(*nextBad, *nextGood);
  }
  arr.resize(distance(arr.begin(), nextBad));
}
void solution4Dimitri(vector<ele> & arr){
  auto leftMostBad = find_if(arr.begin(), arr.end(), isBad);
  if (leftMostBad == arr.end()) return;
  
  for(auto it=leftMostBad+1; it<arr.end(); ++it){
    if (isBad(*it)) continue;
	*leftMostBad=*it;
	++leftMostBad;
  }
  arr.resize(distance(arr.begin(), leftMostBad));
}
//Best solution IMHO
void solution4NoItr(vector<ele> & arr){
  auto leftMostBad = distance(arr.begin(), find_if(arr.begin(), arr.end(), isBad));
  if (leftMostBad == arr.size()) return;
  
  for(auto it=leftMostBad+1; it<arr.size(); ++it){
    if (isBad(arr[it])) continue;
	assert(leftMostBad<=it);
	arr[leftMostBad]=arr[it];
	++leftMostBad;
  }
  arr.resize(leftMostBad);
}
int main(){
  vector<ele> arr={1,3,4,5,-51,-33,8,16,17,-31,20,-28,-27,24,-10,25,-26,-28};
  solution4NoItr(arr);
  dump(arr);
}
/*CVA coding question. general requirements: don't use global variables
requirement 1: Given a vector (not a linked list) and a predate function, remove all bad elements
requirement 2: constant space
requirement 3: linear time
requirement 4: preserve order
*/