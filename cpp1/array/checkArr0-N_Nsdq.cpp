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
bool isChar(Val val){ return val < 0 || sz <= val;}
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
void solution1(){ //my home-grown solution
  dump(0, "original");
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
  }
  for(auto item: a) assert(isChar(item));
  dump(9999999999999, "game over");
}
void solution2(){ //based on XR's email
  for(auto & item: a) ++item;
  dump(0, "upsize");
  for(auto & upsized: a){
    auto idx = abs(upsized)-1;
    if (a[idx] >= 0)
        a[idx] *= -1; //flip sign
    else
        cout<<idx<<" marked as duplicated\n";
  }
}
void check1array(vector<Val> _v){
  a = move(_v); //the argument object is no longer needed
  sz=a.size();  
  solution1();
}
int main(){
  check1array({4,1,2,4,0,2,6,1});
  check1array({0,1,2,4,0,2,3,1});
  check1array({1,2,0,2,0});
  check1array({6,1,2,4,3,5,0});
}
/* Requirement: https://wp.me/p74oew-55f
= means populated exactly once
- means vacated i.e. required value missing
x means shared by multiple instances of this value
*/
