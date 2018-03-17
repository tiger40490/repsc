//showcase type alias
//showcase stable_sort. Actually std::sort happens to be stable in this case
#include <iostream>
#include <vector>
#include <algorithm>
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
void solution4(vector<ele> & arr){
  auto nextBad=arr.begin(); //next good
  auto nextGood=arr.begin(); //next bad
  for(;;){
    nextBad = find_if(nextBad, arr.end(), isBad);
    if (nextBad == arr.end()) break;
	nextGood =find_if(max(nextBad+1, nextGood), arr.end(), isGood);
    if (nextGood == arr.end()) break;
	swap(*nextBad, *nextGood);
  }
  cout<<*nextBad<<endl;
  dump(arr);
}
void solution3(vector<ele> & arr){
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

int main(){
  vector<ele> arr={1,3,-51,-33,8,16,17,-31,20,-28,-27,24,-10,25};
  solution4(arr);
}
/*CVA coding question. general requirements: don't use global variables
requirement 1: Given a vector (not a linked list) and a predate function, remove all bad elements
requirement 2: constant space
requirement 3: linear time
requirement 4: preserve order
*/