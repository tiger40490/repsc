//showcasing std::move
//showcasing typedef to differentiate position vs value
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
typedef int Val;
typedef size_t Pos;
vector<Val> a;  
size_t sz=0;
bool isFake(Val val){ return val < 0 || sz <= val;}
void dump(Pos pos, string headline=""){
  cout<<"-------- "<<headline<<" .. current position == "<<pos<<endl;
  for(Pos i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
  for(Pos i=0; i<sz; ++i) {
    if (isFake(a[i])) cout<<(char)a[i]<<"\t";
    else cout<<a[i]<<"\t";
  }
  cout<<endl;
}
void check1array(vector<Val> _v){
  a = move(_v); //the argument object is no longer needed
  sz=a.size();
  dump(0, "original");
	for (Pos i=0; i<sz; ++i){
    Pos mf = i; //moved from
    Val th=a[i]; /*target home*/
    while(1){
      if (isFake(th)){break;}
      if (th == a[th] || a[th] == '-'){
        if (!isFake(a[mf])) a[mf] = '-'; 
        a[th] = '=';
        //dump(i, "after moving");
        break;
      }else if('=' == a[th] || a[th] == 'x'){
        if (!isFake(a[mf])) a[mf] = '-'; 
        a[th] = 'x';
        //dump(i, "after x");
        cout<<th<<" marked as duplicated\n";
        break;
      }
      if (!isFake(a[mf])) a[mf] = '-'; 
      
      Val evict = a[th];
      mf = th;
      assert( !isFake(a[th]) && a[th] != th);
      a[th] = '=';
      th = evict;
      //dump(i, "after evicting");
      cout<<evict<<" = evicted object from Position "<<mf<<endl;
    }//end of while loop, go back to for loop
  }
  dump(9999999999999, "game over");
}
int main(){
  check1array({4,1,2,4,0,2,6,1});
  check1array({0,1,2,4,0,2,3,1});
  check1array({1,2,0,2,0});
  check1array({6,1,2,4,3,5,0});
}
/* Requirement: https://wp.me/p74oew-55f
= means populated correctly
- means vacated
x means shared by multiple instances of this value
*/
