//showcasing std::move
//showcasing for loop with auto &
//showcasing typedef to differentiate position vs value
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
typedef int Val;
typedef size_t Pos;
vector<Val> a;  
size_t sz=0;
bool isChar(Val val){ return val < 0 || sz < val;}
void dump(Pos pos, string headline=""){
  cout<<"-------- "<<headline<<" .. current position == "<<pos<<endl;
  for(Pos i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
  for(Pos i=0; i<sz; ++i) {
    if (isChar(a[i])) cout<<(char)a[i]<<"\t";
    else cout<<a[i]<<"\t";
  }
  cout<<endl;
}
void solution1(){ /*my home-grown solution
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
  dump(0, "upsize");
  for(auto const upsized: a){
    auto const orig = abs(upsized)-1;
    if (a[orig] >= 0)
  a[orig] *= -1;
    else
  cout<<orig<<" marked as duplicated\n";
  }
}
//////////// by CSY
void swap(int i, int j){
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}
bool isDuplicate(int i, int j){
  if (a[i] == a[j]){
    cout << a[i] <<" marked as duplicated\n";
  }
  return a[i] == a[j];
}
void solution3(){
  for (int i=0; i < sz; i++){
    while (a[i] != i && isDuplicate(a[i], a[a[i]]) == false)
      swap(i, a[i]);
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
  check1array({0,1,2,4,0,2,3,1});
  check1array({1,2,0,2,0});
  check1array({6,1,2,4,3,5,0});
}
/* Requirement: https://wp.me/p74oew-55f
*/
