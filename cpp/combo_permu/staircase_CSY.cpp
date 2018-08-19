//#include <map>
//#include <unordered_map>
#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

template<typename T,             int min_width=8> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
using Step=int;

int main(){
  vector<Step> v={1,2,3,5};
  cout<<v;
}/*
--jargon file:

a STEP from LEVEL 0 to 2 has LENGTH=2, and skips level 1; a PATH consists of 1 or more STEPS; a FORMULA is a complete PATH, and always starts at level 0 and may hit intermediate levels #2, #5, #6 ...

--BFT solution. suppose N = 5. We model each path as a directory path from root. Each queue item is a path represented by a linked list or vector of capacity N.

I hope this solution avoids duplicates ..

enqueue all "first levels" /1; /2; /3; /4; /5
then dequeue and visit first path i.e. "1". In this case, there are 4 levels remaining in the staircase, so enqueue /1/1;  /1/2;  /1/3;  /1/4
then dequeue and visit 2nd path in the queue i.e. "/2". enqueue /2/1; /2/2;  /2/3
Every time (after dequeue) we see a path has total length==N, we print it out as a formula.
*/