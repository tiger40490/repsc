//showcasing std::move
//showcasing for loop with auto &
//showcasing typedef to differentiate position vs value
#include<iostream>
#include<vector>
#include<assert.h>
#define ss if(1>2)cout
using namespace std;
typedef int Val;
typedef size_t Pos;
vector<Val> a;  
size_t sz=0;
bool isChar(Val val){ return val < 0 || sz < val;}
void dump(Pos pos, string headline=""){
  cout<<"-------- "<<headline<<" .. current position == "<<pos<<endl;
  for(Pos i=0; i<sz; ++i) {
    if (isChar(a[i])) cout<<(char)a[i]<<"\t";
    else cout<<a[i]<<"\t";
  }
  cout<<endl;

  for(Pos i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
}
void solution1(){ /*my home-grown solution. Lengthy, powerful, efficient
= means populated exactly once
- means vacated i.e. required value missing
x means shared by multiple instances of this value */
  for (Pos i=0; i<sz; ++i){
    Pos mf = i; //moved from
    Val th=a[i]; /*target home*/
    while(1){
      if (isChar(th)){break;}
      if (th == a[th] || a[th] == '-'){
        if (!isChar(a[mf])) a[mf] = '-'; 
        a[th] = '=';
        //dump(i, "after moving");
        break;
      }else if('=' == a[th] || a[th] == 'x'){
        if (!isChar(a[mf])) a[mf] = '-'; 
        a[th] = 'x';
        //dump(i, "after x");
        cout<<th<<" marked as duplicated\n";
        break;
      }
      if (!isChar(a[mf])) a[mf] = '-'; 
      
      Val evict = a[th];
      mf = th;
      assert( !isChar(a[th]) && a[th] != th);
      a[th] = '=';
      th = evict;
      //dump(i, "after evicting");
      cout<<evict<<" = evicted object from Position "<<mf<<endl;
    }//end of while loop, go back to for loop
  }//for-loop over the positions
  for(auto item: a) assert(isChar(item));
  dump(99999, "game over");
}
void solution2(){ //based on XR's email
  for(auto & item: a) ++item;
  dump(0, "upsized");
  for(auto const upsized: a){
    auto const orig = abs(upsized)-1;
    if (a[orig] >= 0)
      a[orig] *= -1;
    else
      cout<<orig<<" marked as duplicated\n";
  }
}
// returns true iff swapped
bool trySwap(Pos cur, int val){
  if(val==cur)return false;//current position already correct
  if( a[val] == a[cur] ) { // no point swapping
    //target position has correct value, but current position is a bad duplicate of that value
    assert (a[val] == val); 
    assert (a[cur] != cur);
    return false; 
  }
  std::swap(a[val], a[cur]);
  return true;
}
void solution3(){ //inspired by CSY
    //keep updating (by swap) a[0] node until it's filled correctly, or a[a[0]] node is filled correctly. Then move on to a[1].
    for(Pos i=0; i<sz;){
      if ( ! trySwap(i, a[i]) ) ++i;
    }dump(99, "end of solution3");
    
    //now we can easily output dupe values and missing values :)
    for(Pos i=0; i<sz; ++i){
      if (a[i] == i) continue;
      cout<<i<<" -- is missing\n";
      cout<<a[i]<<" ++ marked as duplicated\n";
    }
    cout<<"^^^ end of result dump (empty if clean) ^^^\n";
}
//////////// by CSY
bool notSame(Pos i, Pos j){
  if (a[i] == a[j]){
    cout << a[i] <<" marked as duplicated\n";
  }
  return a[i] != a[j];
}
void solutionByCSY(){ // at a given index, swap until it gets the correct value or a dupe
  for (Pos idx=0; idx < sz; idx++){
    ss<<"idx = "<<idx<<endl;
    while (       idx != a[idx] && 
      notSame  (a[idx],a[a[idx]])){
      std::swap(a[idx],a[a[idx]]);
      ss<<idx<<" swapping "<<a[idx]<<endl;
    }
    //dump(idx);
  }
}
void check1array(vector<Val> _v){
  a = move(_v); //the argument object is no longer needed
  assert(0==_v.size() && "0 != size of vector after robbing");
  sz=a.size();  
  dump(0, "original");  
  solution3();
}
int main(){
  check1array({4,1,2,4,0,2,6,1});
  //return 0;
  check1array({0,1,2,4,0,2,3,1});
  check1array({1,2,0,2,0});
  check1array({2,2,2,2});
  check1array({6,1,2,4,3,5,0});
}
/* Requirement: https://wp.me/p74oew-55f
*/
