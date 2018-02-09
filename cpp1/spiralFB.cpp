#include <iostream>
#include <vector>
#include <deque>
#include <assert.h>
#define ss if (1>0) cout
using namespace std;
int const N = 3; // goal: print a 4x4 matrix
typedef deque<deque<int>> Square;
Square seed1 = {{1}};
Square seed2 = {{4,3},{1,2}};
Square & sq = N%2? seed1 : seed2;

void dump(Square const & arr){
  size_t const n = arr.size();
  for(int row=0; row<n; ++row){
   for(int col=0; col<n; ++col) cout<<arr[row][col]<<"\t";
   cout<<endl;
  }
}
void grow1(){
  //Square & sq = seed2; //seed1
  size_t const len = sq.size();
  for (int row = 0; row <len; ++row){
	  sq[row].push_front(0);
	  sq[row].push_back(0);
  }
  sq.push_front(deque<int>(len+2,0));
  sq.push_back(deque<int>(len+2,0));
  size_t const newlen = sq.size();
  //populate the new cells
  int i=len*len+1;
  for(int row=1; row<newlen; ++row) sq[row][0] = i++;
  for(int col=1; col<newlen; ++col) sq[newlen-1][col] = i++;  
  for(int row=newlen-2; row>=0; --row) sq[row][newlen-1] = i++;
  for(int col=newlen-2; col>=0; --col) sq[0][col] = i++;  
  dump(sq);
}	
int main(){
    grow1();
    grow1();
}
/*Requirement: https://wp.me/p74oew-4ae
*/