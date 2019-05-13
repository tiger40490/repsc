// This recursion-in-loop technique is powerful but easily hits SOF. If no other choice, we may need to convert recursion into iterative.
#include <iomanip>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<typename T,             int min_width=2> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   //for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   //os<<endl;
   return os;
}
vector<vector<int> > solutions;
vector<int> partial;
vector<int> const * cand;
int target=0;
bool isPermutation = false;
void recurs(int gap, int startIndex){ //Warning: SOF if N is large like 99999
  if (isPermutation) startIndex = 0;
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
vector<vector<int> > combinationSum(vector<int>& candidates, int tgt) {
  cout<<tgt<<" to be broken into v v v v v v    "<<candidates;
  isPermutation=false;
  cand = &candidates;
  solutions.clear();
  partial.clear();
  target = tgt;
  recurs(target, 0);
  return solutions;
}
void rerun(bool isP){
  isPermutation = isP;
  solutions.clear();
  partial.clear();
  recurs(target, 0);  
}

int main(){
  combinationSum(*(new vector<int>({2,3,4})), 9);
  assert(solutions.size() == 3);
  rerun(true); //with isPermutation
  assert(solutions.size() == 4 + 1 + 6);
  combinationSum(*(new vector<int>({2,3,4})), 7);
  assert(solutions.size() == 2);
  rerun(true); //with isPermutation
  assert(solutions.size() == 3 + 2);
  combinationSum(*(new vector<int>({2,3,6,7})), 7);
  combinationSum(*(new vector<int>({2,3,5})), 8);
  assert(solutions.size() == 3);
}/*Req: https://bintanvictor.wordpress.com/2018/08/05/combination-sum-reusable-backtracking/
Q1: generate all combinations
Q2: generate all permutations of all combinations
*/