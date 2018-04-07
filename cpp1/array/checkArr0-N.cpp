//showcasing std::move
//showcasing typedef to different position vs value
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
typedef int Val;
typedef size_t Pos;
vector<Val> a;  
size_t sz=0;
void dump(Pos pos, string headline=""){
  cout<<"-------- "<<headline<<" .. current position == "<<pos<<endl;
  for(Pos i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
  for(Pos i=0; i<sz; ++i) {
    if (a[i]< 0 || sz <= a[i]) cout<<(char)a[i]<<"\t";
    else cout<<a[i]<<"\t";
  }
  cout<<endl;
}
void solve1(vector<Val> _v){
  a = move(_v); //the argument object is no longer needed
  sz=a.size();
  dump(0, "original");
	for (Pos i=0; i<sz; ++i){
    Pos mf = i; //moved from
    Val th=a[i]; /*target home*/
    while(1){
      if (th < 0 || sz <= th){break;}
      if (th == a[th] || a[th] == '-'){
        if (0 <= a[mf] && a[mf] < sz) a[mf] = '-'; 
        a[th] = '=';
        dump(i, "after moving");
        break;
      }else if('=' == a[th] || a[th] == 'x'){
        a[mf] = '-';
        a[th] = 'x';
        dump(i, "after x");
        cout<<th<<" marked as duplicated\n";
        break;
      }
      if (0 <= a[mf] && a[mf] < sz) a[mf] = '-'; 
      
      Val evict = a[th];
      mf = th;
      assert( 0<=a[th] && a[th]<sz && a[th] != th);
      a[th] = '=';
      th = evict;
      dump(i, "after evicting");
      cout<<evict<<" = evicted object from Position "<<mf<<endl;
    }//end of while loop, go back to for loop
  }
  dump(9999999999999, "game over");
}
int main(){
  solve1({1,2,0,2,0});
  solve1({1,2,4,3,0});
}
/* Requirement: https://bintanvictor.wordpress.com/2018/04/07/check-array-of-0-to-n-nasdaq/
= means the correct number is now occupying
- means vacated
x means multiple objects of this value are found
*/