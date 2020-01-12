#include <cassert>
#include <deque>
#include <iostream>
#include <iomanip>
using namespace std;
using Idx=size_t;
template<typename T,             int min_width=2> ostream & operator<<(ostream & os, deque<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}
int linearSolution(string const & str){
  deque<char> arr(str.begin(), str.end());
  while(arr.size()){
    if (arr.front()=='w'){
      arr.pop_front();
    }else{
      break;
    }
  }
  while(arr.size()){
    if (arr.back()=='w'){
      arr.pop_back();
    }else{
      break;
    }
  }
  if (arr.empty()) return 0; //all same color
  cout<<arr; //after removing all leading/trailing whites
  Idx le=0, ri=arr.size()-1;
  deque<Idx> wh2remove; 
  for (Idx i=0; i<=ri; ++i){
    if (arr[i] == 'w') wh2remove.push_back(i);
  }
  if (wh2remove.empty()) return 0;
  cout<<wh2remove;
  int ret=0;
  do{
    cout<<wh2remove;
    Idx front=wh2remove.front(), back=wh2remove.back();
    size_t d1=front-le, d2=ri-back;
    if (d1 <= d2){ //move front out
      ret += d1;
      wh2remove.pop_front();
      ++le;
      cout<<le<<" = le\n";
    }else{
      ret += d2;
      wh2remove.pop_back();
      --ri;
      cout<<ri<<" = ri\n";
    }
    //cout<<ret<<" is the new ret\n";
    assert(le<=ri);
  }while(wh2remove.size());

  return ret;
}
int main(){
  assert(6==linearSolution("rwrwrwrwrw"));
  assert(3==linearSolution("rwrwrrrrw"));
  assert(2==linearSolution("wwrrwwrwwww"));
  assert(3==linearSolution("wwwrrwrrrwrwww"));
}/*Req: 
https://leetcode.com/discuss/interview-question/414660/microsoft-oa-2019-min-swaps-to-group-red-balls
*/
