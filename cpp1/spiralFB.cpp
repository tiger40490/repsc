//todo: //we can get rid of this ALL thing and avoid the cloning
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

void dump(int const n){
  assert (n > 0 && "bad input");
  Square arr = All[n];
  for(int row=0; row<n; ++row){
   for(int col=0; col<n; ++col) cout<<arr[row][col]<<"\t";
   cout<<endl;
  }
}
void shiftCopy(int const n){
  Square clone = All[n];
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
  
  All[clone.size()]=(clone);
  dump(len+2);
}	

int main(){
	All[1] = seed1;
	All[2] = seed2;
	dump(2);
	shiftCopy(2);
}
/*Requirement: https://wp.me/p74oew-4ae
*/