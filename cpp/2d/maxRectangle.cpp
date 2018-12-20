/*
sugg: work out the logic for a simple staircase first. Once clear, work out one more staircase on the right.

why unconditionally save current bar? Cos it can be part of a growing rectangle

why do we pop() until the remaining bars (in stack) are strictly lower than current bar? cos for such a small bar, the best rectangle is not known yet and could extend to the right beyond current column. Imagine the bar of height 1 covering entire base

Why O(N) per-row? cos the stack only holds up to N items and each item is pushed and popped exactly once so all stack operations add up to O(N). 

todo 2: had better be > not >=
showcase: separate out first inner for-loop so as to focus on the core algo
showcase: clever tweaks to enable unit testing of the histogram algo
*/
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <iomanip>
#include <cassert>
#define STACK_TOP bar[s.top()]
using namespace std;
using bsz=size_t; //bar size
using idx=size_t; //index into array
using pos=pair<idx, idx>;

int const UNASSIGNED = -1;
struct rec{ //part of an early stage idea
  bsz westbar;// how many contiguous black pixels on left including myself
  bsz northbar; //how many contiguous black pixels above, including myself
  
  //zero if current cell is white. Actually, white pixels may not even exist in the data structure
  
  list<pos> bbeh; /* bestBoxEndingHere i.e. largest rectangles having current pixel as the south-east corner. Box in this list must not be the westbar or northbar.
  
  In some cases, two rectangles have the same area, larger than all other rectangles, but this list size will always be much smaller than N.
  
  This list may contain the current pixel alone as a tiny "box", in the trivial case.
  */
};
ostream & operator<<(ostream & os, rec const & n){
  os<<"[ ";
  os<<" ]";
  return os;
}
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}

/*https://leetcode.com/problems/maximal-rectangle/discuss/29064/A-O(n2)-solution-based-on-Largest-Rectangle-in-Histogram
*/
int histo(size_t const exp, vector<vector<char> > const matrix) {
  if (matrix.size() <= 0 || matrix[0].size() <= 0) return 0;
    
  int const rcnt = matrix.size();
  int const n = matrix[0].size() + 1;
  int const lastColIdx = n-2;
  int maxArea = 0;
  vector<bsz> bar(n, 0);
  
  for (int i = 0; i < rcnt; ++i) {
    for (idx j = 0; j <= lastColIdx+1; ++j) {
      if (j <= lastColIdx) { //up to last real column. Fake col untouched
        if (matrix[i][j] == 1) bar[j] += 1;
        else bar[j] = 0;
      }
    }
    /* histo bars updated for this row, now compute max rectangle in histogram
    
    Below is the central algo -- the rectangle-in-histogram algo. Too tricky so I set up special test fixture just to uncover the logic.
    */
    //bar = {33,11,22,33,22}; bar.push_back(0);
    cout<<bar;
    stack<idx> s;
    vector<bsz> vec;
    for (idx j = 0; j <= bar.size()-1; ++j) {
      bsz h =0, width = 0;
      cout<<"\n  == "<<j<<" == j; bar[j] = "<<bar[j]<<endl;
      
      while (s.size() && STACK_TOP >= bar[j]) {//current bar is (equal or) shorter than previous bar
        auto idxOfH=s.top();
        h = STACK_TOP;
        cout<<h<<"/"<<idxOfH<<" = stack.top() in while-loop\n";
        s.pop();
        
        //somehow compute the width for the rectangle of height h
        width = s.empty() ? j : j - s.top() - 1;
        //update maxArea .. observer code
        if (s.empty()){
          cout<<j<<" = j = width (stack empty)\n";
          for (auto prevStackItem: vec)
            assert(prevStackItem >= h); 
        }
        vec.push_back(h);
        if (h * width > maxArea){
          maxArea = h * width;
          cout<<maxArea<<"sqm is the updated maxArea\n";
        }
      }
      if (!s.empty()){ //observer
          assert(STACK_TOP < bar[j] && "push only when current bar is higher than all remainders in stack");
      }
      
      s.push(j);
      for (auto tmp=s; tmp.size(); tmp.pop()){ //observer
          cout<<" "<<bar[tmp.top()]<<"/"<<tmp.top();
      }
      cout<<"..is the stack after popping all equal/shorter and pushing current bar\n";
    }// inner for-loop
    //exit(0); 
  }//outer for-loop
  cout<<maxArea<<" = maxArea\n";
  assert(exp==maxArea);
  return maxArea;
}
int test11(){
  histo(4, {
  {1,1,0,1},
  {1,0,1,1},
  {1,1,1,1}});
}
int test15(){
  histo(6, {
  {1,1,0,1,0},
  {1,0,1,1,1},
  {1,1,1,1,1}});
}
int test22(){
  histo(5, {
  {1,1,0,1,0},
  {0,0,1,1,0},
  {1,1,1,1,1}});
}
int test33(){
  histo(6, {
  {1,1,1,0,0},
  {0,1,1,1,0},
  {1,1,1,1,1}});
}
int test44(){
  histo(6, {
  {1,1,0,1},
  {0,1,0,1},
  {0,1,1,1},
  {1,1,1,1}});
}
int testStairs(){
  histo(6, {
  {0,0,0,1},
  {0,0,1,1},
  {0,1,1,1},
  {1,1,1,1}});
}
int main() {
  test11();
  test15();
  test22();
  test33();
  test44();
  testStairs();
}
/* Req: see blog. 

--Here's my hopefully O(NN) idea, but not a solution yet. In fact, it may not work at all.
* One pass to count how many black pixels across entire matrix. Denote this number as K. Size a hash table to K buckets, so as to preempt rehashing. More memory efficient than a shadow matrix. Each record in the data structure is described in code. The hashmap is {position -> record}

* In the same pass also build a linked list (blacklist) of all black pixels, first row to last row. Every list node holds a position of a black pixel. Blacklist has length K, starting at left-most black pixel on top "useful" row and ending at right-most black pixel on bottom useful row.

First pass is O(NN). Zero calculation.

* One pass through the blacklist to populate the northbar field of every record. Just use the upper neighbor and increment ...

* One pass through the blacklist to populate the westbar field of every record. 

So far, every pass is O(NN) at most, or possibly O(K).

* Last pass is complex. Scan through the black list to update the bbeh of each record. When we update bbeh@[5,16], we will use three neighbor records at [4,15] [5,15] [4,16]. 

There are many possible scenarios but I believe in all cases, we can [1] find the largest rectangle(s) ending at [5,16] using nothing but the three neighbor records. 

[1] If we always can, then Last pass is O(K). Worst scenario would hit a few rectangles in one of the three bbeh lists but the data size is always rather small. 

Note if a neighbor like [4,15] is not in hashmap, then it's a white pixel, so westbar, northbar and bbeh are zeros.

This is one of the hardest algo challenges I have seen in 10 years. If I come up with my very own solution I would feel emensely proud. I do feel I'm on the /brink/ of breakthrough.
*/
