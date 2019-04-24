//showcase accumulate on part of a vector
//showcase populating a vector with a custom default value
//showcase priority_queue
//showcase global operator<() on two priority_queues
//showcase std::move
//This implmentation has visulization feature to "paint" the original array in different colors, where each colored section is one subarray.
#include <assert.h>
#include <vector>
#include <queue>
#include <numeric>
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
int T = 0;// each group/subarray can be up to this size
size_t grouped=0; //how many nodes already assigned to groups
Cost grandTotal=0;
vector<ele> arr;

void demarcate1group(Idx le, Idx ri, Idx peak){
  static char ch='a';
  static vector<char> paint;
  if (grandTotal == 0) paint=vector<char>(arr.size(), ' ');
  grandTotal += arr[peak];
  grouped += ri-le;
  ss<<"new subarray: [ "<<le <<" - "<<ri-1<<" ], peak Idx = "<<peak<<" , grandTotal = "<<grandTotal<<endl;
  for (Idx i=le; i<ri; ++i) paint[i]=ch;
  ss<<arr<<paint;
  ++ch;
}

bool operator <(priority_queue<ele> aa, priority_queue<ele> bb){
    assert(aa.top() == bb.top() && "max is the current peak");
    aa.pop(); bb.pop();
    while (aa.size()){
        if    (aa.top() <  bb.top()) return true;
        if    (aa.top() >  bb.top()) return false;
        assert(aa.top() == bb.top());
        aa.pop();
        bb.pop();
    }
    return false; //if every comparison shows equal
}

void recurs(Idx le, Idx ri){ //ri is one past the range
  ss<<le<<" === le; ri === "<<ri<<endl;
  Idx peak=le; 
  for (Idx i=le+1; i<ri; ++i){
    if (arr[i] > arr[peak]) peak = i;
  }
  if (ri-le <= T){
    if (ri > le) demarcate1group(le,ri, peak);
    //else there's zero node in the range.
    return;
  }
  ss<<peak<<" = peak idx\n";
  Idx groupLe = max((int)le, (int)peak-T+1); //cast required to avoid overflow
  priority_queue<ele> bestWindow(arr.begin()+groupLe, arr.begin()+groupLe+T);
  ss<<"sliding window starting at "<<groupLe<<endl;
  //now slide the window
  for (Idx tryLe = groupLe+1; tryLe<=min(peak,ri-T); ++tryLe){
    priority_queue<ele> newWindow(arr.begin()+tryLe, arr.begin()+tryLe+T);
    if (bestWindow < newWindow){
      bestWindow = newWindow;
      groupLe = tryLe;
      ss<<"better window starting at "<<groupLe<<endl;
    }
  }
  demarcate1group(groupLe, groupLe+T, peak);
  recurs(le, groupLe);
  recurs(groupLe+T, ri); //what if this group is smaller than T
}
Cost solve(vector<ele> _tmp){ 
  grandTotal = grouped = 0;
  arr = move(_tmp);
  assert(_tmp.size() == 0);
  recurs(0, arr.size());
  assert(grouped == arr.size());
  return grandTotal;
}
int main(){
  T = 3;
  assert(149 == solve({49,50,99,0,98})); 
  assert(23 == solve({2,7,8,1,6,5,0,3,9,4})); 
  assert(24 == solve({1,7,8,2,6,5,3,0,9,4})); 
  assert(24 == solve({2,7,8,1,6,5,3,0,9,4})); 
  assert(19 == solve({8,1,3,2,5,9,7,0})); 
  assert(22 == solve({8,1,3,2,5,9,7,6})); 
}/*Req: https://bintanvictor.wordpress.com/2018/06/19/min-cost-partitioning-flextrade/
*/
