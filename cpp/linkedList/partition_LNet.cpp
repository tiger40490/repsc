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
I myPartition(I beg, I const end, P isgood){
  //first adjust e
  auto e = prev(end);
  while ( !isgood(*e)){ // not good
    if (e == beg) return e;
    --e;
  }
  assert ( isgood(*e) && "e now points to a good node");
  for (;;){
    if (beg == e){
      cout<<111111<<endl;
    }
    //adjust beg and check exit conditions
    while(isgood(*beg)){
      ++beg;
      if (beg==e){
        cout<<22222<<endl;
        return e;
      }
    }
    assert ( !isgood(*beg) && "beg now points to a bad node");
    //adjust e and check exit conditions
    while(!isgood(*e)){
      --e;
      if (beg==e){
        cout<<22222<<endl;
        return e;
      }
    }
    assert ( isgood(*e) && "e now points to a good node");
    swap(*beg, *e);
  }
  return end; 
}

bool isOdd(int i){ return i%2; }

int main(){
  list<int> li={1,2,3,4,5,6,7,8,9};
  auto firstBad = myPartition(li.begin(), li.end(), isOdd);
  if (firstBad == li.end()){
    cout<<"no bad node\n";
  }else{
    cout<<*firstBad<<endl;
  }
  cout<<li<<endl;
}