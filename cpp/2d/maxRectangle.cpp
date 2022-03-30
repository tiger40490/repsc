#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;
using bsz=size_t; //bar size
using idx=size_t; //index into matrix
using pos=pair<idx, idx>;

int const UNASSIGNED = -1;
struct rec{
  bsz westbar;// how many contiguous black pixels on left including myself
  bsz northbar; //how many contiguous black pixels above, including myself
  
  //zero if current cell is white. Actually, white pixels may not even exist in the data structure
  
  list<pos> bbeh; /* bestBoxEndingHere i.e. largest rectangles having current pixel as the south-east corner. Box in this list must not be the westbar or northbar.
  
  In some cases, two rectangles have the same area, larger than all other rectangles, but this list size will always be much smaller thn N.  
  
  This list may contain the current pixel, in the trivial case.
  */
};
ostream & operator<<(ostream & os, rec const & n){
  os<<"[ ";
  os<<" ]";
  return os;
}

int main() {
}
/* Req: given a N-by-N marix of black/white pixels, find the largest all-black rectangle. It might be a bar of width 1 length 22 (area 22), or a single dot (area 1). 

--Here's my O(NN) idea
* One pass to count how many black pixels across entire matrix. Denote this number as K. Size a hash table to K buckets, so as to preempt rehashing. More memory efficient than a shadow matrix. Each record in the data structure is described in code. The hashmap is {position -> record}

* In the same pass also build a linked list (blacklist) of all black pixels, first row to last row. Every list node holds a position of a black pixel. Blacklist has length K, starting at left-most black pixel on top row and ending at right-most black pixel on bottom row.

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
