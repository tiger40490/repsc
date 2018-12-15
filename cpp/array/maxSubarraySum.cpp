// showcasing macro for long var name
//
#include<iostream>
#include<vector>
#include<climits>
#include<cassert>
#define ss if(1>0) cout
#define meh max_ending_here
using namespace std;

vector<int> vec = {-2, -3, 4, -1, -2, 1, 5, -3};
int implG4G(){ // https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
  int ret = INT_MIN, meh = 0;

  for (int i = 0; i < vec.size(); ++i) {
    meh = meh + vec[i];
    ret = max(ret, meh); //must come between the meh update!
    if (meh < 0) meh = 0;
    ss<<meh<<" = meh; ret = "<<ret<<endl;
  }
  cout << ret << " = G4G Maximum contiguous sum\n";
  return ret;
}
int le, bestLe, bestRi;
int implPY(){ //based on my python solution
  le=INT_MIN; 
  bestLe=INT_MIN; 
  bestRi=INT_MIN;
  int ret = INT_MIN, meh = 0;

  for (int i = 0; i < vec.size(); ++i) {
    if (meh < 0) {
      meh = vec[i];
      le=i; //left marker of the current subarrayEndingHere
    }else{
      meh = meh + vec[i];
    }
    //meh = vec[i] + meh*(meh>0); //basically equivalent to the above
    
    //Code below is passive-observer, not affecting the algorithm
    if (ret < meh){
      ret = meh;
      bestLe=le;
      bestRi=i;
    }
    ss<<meh<<" = meh; ret = "<<ret<<endl;
  }
  cout << ret << " = Maximum contiguous sum based on python implementation\n";
  return ret;
}
int main(){
  assert (implG4G()==7 && 7==implPY());  
  assert (bestLe==2 && 6 == bestRi);
  vec = {-2, -3, -4, -1, -2, -1, -5, -3};
  assert (implG4G()==-1 && -1==implPY());  
}
/* Requirement: print largest contiguous array sum 
https://bintanvictor.wordpress.com/2017/02/14/7672/ 
*/
