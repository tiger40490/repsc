#include <assert.h>
#include <vector>
#include <iostream>
#include <iomanip>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;
typedef int ele; //element in array
typedef size_t Idx;
typedef size_t Cost;

template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
size_t const T = 3;// each group/subarray can be up to this size
size_t grouped=0; //how many nodes already assigned to groups
Cost grandTotal=0;
vector<ele> arr;

void makeGroup(Idx le, Idx ri, Idx peak){
	static char ch='a';
	static vector<char> paint(arr.size(), ' ');
	grouped += ri-le;
    grandTotal += arr[peak];
	ss<<"new subarray: [ "<<le <<" - "<<ri-1<<" ], peak Idx = "<<peak<<" , grandTotal = "<<grandTotal<<endl;
	for (Idx i=le; i<ri; ++i) paint[i]=ch;
	ss<<arr<<paint;
	++ch;
}

void recurs(Idx le, Idx ri){ //ri is one past the range
  ss<<le<<" === le; ri === "<<ri<<endl;
  Idx peak=le; 
  for (Idx i=le+1; i<ri; ++i){
    if (arr[i] > arr[peak]) peak = i;
  }
  if (ri-le <= T){
	  if (ri > le) {
		makeGroup(le,ri, peak);
	  }
	  return;
  }
  ss<<peak<<" = peak idx\n";
  Idx groupLe = le; 
  if (peak > T-1) groupLe = peak-T+1;
  Cost tot = 0; for (int i=groupLe; i<groupLe+T; ++i) tot += arr[i]; 
  Cost max = tot;
  //ss<<"sliding window starting at "<<groupLe<<" with tol = "<<max<<endl;
  //now slide the window
  for (Idx tryLe = groupLe; tryLe<min(peak,ri-T); ++tryLe){
	tot += arr[tryLe+T] - arr[tryLe];
	if (tot > max){
	  max = tot;
	  groupLe = tryLe+1;
	  ss<<"better window starting at "<<groupLe<<" with sum = "<<max<<endl;
	}
  }
  makeGroup(groupLe, groupLe+T, peak);
  recurs(le, groupLe);
  recurs(groupLe+T, ri); //what if this group is smaller than T
}
Cost solve(vector<ele> _tmp){ 
  grandTotal = grouped = 0;
  arr = move(_tmp);
  ss<<arr;
  recurs(0, arr.size());
  assert(grouped == arr.size());
  return grandTotal;
}
int main(){
  assert(19 == solve({8,1,3,2,5,9,7,0})); 
  assert(22 == solve({8,1,3,2,5,9,7,6})); 
}/*Req: https://bintanvictor.wordpress.com/2018/06/19/min-cost-partitioning-flextrade/
*/