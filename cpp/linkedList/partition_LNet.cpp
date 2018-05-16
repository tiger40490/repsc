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
template<typename I, typename P>
I myPartition(I bb, I const end, P isgood){
  auto ee = prev(end);
  while ( !isgood(*ee)){ // not good i.e. even
    if (ee == bb) return bb;
    --ee;
  }
  assert ( isgood(*ee) && "ee is now initialized to a good node");
  for (;;){
    if (bb == ee){
      cout<<111111<<endl;
    }
    //adjust bb and check exit conditions
    while(isgood(*bb)){
      ++bb;
      if (bb==ee){
        cout<<22222<<endl;
        if (ee == prev(end)) return end;
        return ee;
      }
    }
    assert ( !isgood(*bb) && "bb now points to a bad node");
    //adjust ee and check exit conditions
    while(!isgood(*ee)){
      --ee;
      if (bb==ee){
        cout<<33333333<<endl;
        return ee;
      }
    }
    assert ( isgood(*ee) && "ee now points to a good node");
    //cout<<*bb<<" -swapping- "<<*ee<<endl;
    swap(*bb, *ee);
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
  test1({1,2,3,4,5,6,7,8});
  test1({1,2,3,4,5,6,7,8,9});
  test1({1,3,5,2,4,6,8,7,9});
  test1({1,3,5,7});
}
/*Req: ....
My solution is overcomplicated since I move two rather than one pointer.
*/