//todo: avoid the matrix cloning
//todo: the ALL and dump() should be optional in #ifdef
#include <iostream>
#include <vector>
#include <deque>
#include <assert.h>
#define ss if (1>0) cout
using namespace std;
int const N = 4; // goal: print a 4x4 matrix
typedef deque<deque<int>> Square;
Square seed1 = {{1}};
Square seed2 = {{4,3},{1,2}};
vector<Square> All(99); 

void dump(Square & arr){
  size_t const n = arr.size();
  for(int row=0; row<n; ++row){
   for(int col=0; col<n; ++col) cout<<arr[row][col]<<"\t";
   cout<<endl;
  }
}
void inPlace(){
  Square & clone = seed2; //seed1
  size_t const len = clone.size();
  for (int row = 0; row <len; ++row){
	  clone[row].push_front(0);
	  clone[row].push_back(0);
  }
  clone.push_front(deque<int>(len+2,0));
  clone.push_back(deque<int>(len+2,0));
  size_t const newlen = clone.size();
  //populate the new cells
  int i=len*len+1;
  for(int row=1; row<newlen; ++row) clone[row][0] = i++;
  for(int col=1; col<newlen; ++col) clone[newlen-1][col] = i++;  
  for(int row=newlen-2; row>=0; --row) clone[row][newlen-1] = i++;
  for(int col=newlen-2; col>=0; --col) clone[0][col] = i++;  
  dump(clone);
}	

int main(){
    inPlace();
    inPlace();
}
/*Requirement: https://wp.me/p74oew-4ae
*/