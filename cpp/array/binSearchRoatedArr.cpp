#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;
using pos=int;
template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
class Solution {
public:
    size_t End;
    int _2high(vector<int>& nums, int target) {
        cout<<"2high.. Must be in right segment\n";
        return -1; //to be implemented
    }
    int _2low(vector<int>& nums, int target) {
        cout<<"2low..  Must be in left segment\n";
        vector<int>& a=nums;
        size_t cand = End/2, le=0, ri=End;
        for(;nums[cand]<target; ){
            if (le >= ri){
                cout<<"non-existent\n";
                return -1;
            }
            if (a[le] < a[cand]){
              cout<<"rightward";
              le = cand;
            }else{
              cout<<"leftward";
              ri = cand;
            }
            cand = (le + ri)/2;
            cout<<"  trying "<<cand<<endl;
        }
        if (a[cand] == target) return cand;
        assert(a[le] < target && target < a[cand]); // only need to search between a[0] and a[cand]
        cout<<"binary searching from "<<le<<" to "<<cand<<endl;
        ri=cand;
        for(;le<ri; cand=(le+ri)/2){
          if (a[cand] == target) return cand;
          if (a[cand] < target){ le = cand+1;
          }else{ ri = cand-1;
          }
        }
        return -1;
    }
    int search(vector<int>& nums, int target) {
        vector<int>& a=nums;
        cout<<a;
        End = a.size()-1;
        if (a[0] == target) return 0;
        bool isLeEndTooLow = a[0] < target;

        if (a[End] == target) return End;
        bool isRiEndTooLow = a[End] < target;
        if ( !isLeEndTooLow && isRiEndTooLow ){ //
            cout<<"caught between left-end and right-end:("<<endl;
            return -1;
        }
        assert (a[0] >= a[End]);
        if ( isLeEndTooLow && !isRiEndTooLow ){
          assert (false && "array is monotonic wihtout rotation :(");
        }
        assert (isLeEndTooLow == isRiEndTooLow);
        if (isLeEndTooLow) return _2low(nums, target);
        else               return _2high(nums,target);
    }
} inst;
//////////// new solution based on well-defined modules, ez to test and reason about.
int pivot(vector<int> const & a){// return index of max item. 
  for (pos le=0, ri=a.size()-1;;){
    if (le+1 == ri) return le;
    pos mi=(le+ri)/2;
    if (a[mi] <= a[ri])
      ri=mi;
    else
      le=mi;
    assert(a[le] >= a[ri]);
  }
}
int simplefind(vector<int> const & a, int const needle, pos le, pos ri){ //return index 
  for (;;){
    pos mi = (le+ri)/2;
    if (a[mi] == needle) return mi;
    if (le+1 == ri) return -1;
    if (a[mi] > needle)
      ri=mi;
    else
      le=mi;
  }
}
int searchTgt(vector<int> const & a, int const needle){ //return index or -1
  cout<<a;
  auto peakPos = pivot(a);
  if (needle < a[peakPos+1]) return -2; //too low
  if (needle > a[peakPos])   return -3; //too high
  if (needle >= a[0]) return simplefind(a, needle, 0, peakPos);
  return simplefind(a, needle, peakPos+1, a.size()-1);
}
int main(){
  vector<int> a={33,35,37,39,40,42,44,55,1,3,4,11,22};
  pos found = searchTgt(a, 55);
  cout<<found<<endl;
  return 0;
  auto ret = inst.search(a,42);
  cout<<ret<<" is the answer\n";
}/*Req: https://bintanvictor.wordpress.com/2018/06/23/binary-search-in-rotated-sorted-array/
too long. There must be shorter simpler solutions
*/

