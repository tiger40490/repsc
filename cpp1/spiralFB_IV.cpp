/* showcasing multi-dimensional array syntax using deque of deque
 * showcasing deque constructed on the fly
 */
#include <iostream>
#include <deque>
#include <assert.h>
#define ss if (1>0) cout
using namespace std;
int const N = 4; // requirement: print a NxN matrix
typedef deque<deque<int>> Square;
Square sq = N%2 ? Square({{1}}) : Square({{4,3},{1,2}}); //seeding

void dump(string headline="--"){
  if (!headline.empty()) cout<<"v v v   "<<headline<<"   v v v\n";
  size_t const len = sq.size();
  for(int row=0; row<len; ++row){
   for(int col=0; col<len; ++col) cout<<sq[row][col]<<"\t";
   cout<<endl;
  }
}
void grow(){ //expand by one layer
  size_t const lenB4 = sq.size();
  size_t const lenAf = lenB4 + 2;
  for (int row=0; row<lenB4; ++row){
          sq[row].push_front(0);
          sq[row].push_back(0);
  }
  sq.push_front(deque<int>(lenAf,0));
  sq.push_back (deque<int>(lenAf,0));
  //Now we have a bigger square matrix (not a staggered 2D array. Populate the new cells
  size_t const highestIndex = lenAf-1;
  size_t const nextHighest  = lenAf-2;
  int i = lenB4*lenB4 + 1; //next value to use
  for(int row=1;        row<lenAf; ++row) sq[row][0] = i++;
  for(int col=1;        col<lenAf; ++col) sq[highestIndex][col] = i++;
  for(int row=nextHighest; row>=0; --row) sq[row][highestIndex] = i++;
  for(int col=nextHighest; col>=0; --col) sq[0][col] = i++;
  dump();
}
int main(){
  assert(N>0);
  dump("seed");
  for(int i=(N-1)/2; /*target repetition*/ i>0; --i) grow();
  assert(sq.size() == N);
}
/*Requirement: https://wp.me/p74oew-4ae
*/
