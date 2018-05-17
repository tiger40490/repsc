//todo : check empty range
#include <list>
#include <cassert>
#include <iostream>
#include <iomanip>
using namespace std;

template<typename T,             int min_width=4> ostream & operator<<(ostream & os, list<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   return os;
}
/*invariant: bb is at or before ee. We check this before every 
inc/dec
*/
template<typename I, typename P>
I myPartition(I bb, I const end, P isgood){
  auto ee = prev(end);
  while ( !isgood(*ee)){
    if (ee == bb) return bb; // all bad
    --ee;
  }
  assert ( isgood(*ee) && "ee is now initialized to the last good node in original sequence");
  
  int swapCnt=0;
  for (;;){
    while(isgood(*bb)){
      if (next(bb)==ee){ 
        //cout<<22222<<endl;
        if (ee == prev(end)) return end; //no bad node
        assert(swapCnt);
        assert(!isgood(*ee) && "if there's any swap, then ee must be Bad now");
        return ee;
      }
      ++bb;
    }
    assert ( !isgood(*bb) && "bb now points to a bad node");
    while(!isgood(*ee)){
      if (next(bb)==ee){
        cout<<"both are bad and adjcent"<<endl;
        return bb;
      }
      --ee;
    }
    assert ( isgood(*ee) && "ee now points to a good node");
    //cout<<*bb<<" -swapping- "<<*ee<<endl;
    swap(*bb, *ee);
    ++swapCnt;
  }
  return end; 
}
bool isOdd(int i){ return i%2; }
void test1(list<int> li){
  auto firstBad = myPartition(li.begin(), li.end(), isOdd);
  cout<<li<<" --> ";
  if (firstBad == li.end()){
    cout<<"no bad node\n";
  }else{
    cout<<*firstBad<<endl;
  }
}
int main(){
  test1({4,6,7});
  test1({1,2,3,4,5,6,7,8});
  test1({1,2,3,4,5,6,7,8,9});
  test1({1,3,5,2,4,6,8,7,9});
  test1({1,3,5,7});
}
/*Req: ....
Note our iterator doesn't support comparison.

My solution is overcomplicated since I move two rather than one pointer.
*/