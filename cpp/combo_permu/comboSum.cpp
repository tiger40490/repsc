#include <iomanip>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   //for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   //os<<endl;
   return os;
}
vector<vector<int> > solutions;
vector<int> partial;
vector<int> const * cand;
void recurs(int gap, int startIndex){
  cout<<"trying "<<partial;
  if (gap == 0){
      solutions.push_back(partial);
      cout<<"<-- A solution :)\n";
      return;
  }
  assert(gap > 0);
  for (int i=startIndex; i < cand->size(); ++i){
    auto const & item = (*cand)[i];
    if (gap < item) return;
    partial.push_back(item);
    recurs(gap - item, i);
    partial.pop_back(); //backtrack up the tree
  }
}
vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
  cout<<" v v v v v v "<<candidates;
  cand = &candidates;
  solutions.clear();
  partial.clear();
  recurs(target, 0);
  return solutions;
}

int main(){
  combinationSum(*(new vector<int>({2,3,4})), 7);
  assert(solutions.size() == 2);
  combinationSum(*(new vector<int>({2,3,6,7})), 7);
  combinationSum(*(new vector<int>({2,3,5})), 8);
  assert(solutions.size() == 3);
}/*Req:
*/