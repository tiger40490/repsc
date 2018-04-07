#include<iostream>
#include<vector>
using namespace std;

vector<int> a={1,2,0,2,0};
size_t const sz=a.size();
void dump(int pos, string headline=""){
  cout<<"-------- "<<headline<<" .. current position == "<<pos<<endl;
  for(auto i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
  for(auto i=0; i<sz; ++i) {
    if (a[i]< 0 || sz <= a[i]) cout<<(char)a[i]<<"\t";
    else cout<<a[i]<<"\t";
  }
  cout<<endl;
}
int main(){
  dump(0, "original");
  
	for (size_t i=0; i<sz; ++i){
    size_t mf = i; //moved from
    int th=a[i]; /*target home*/
    while(1){
      if (th < 0 || sz <= th){
        dump(i, "cur is not a num");
        break; 
      }
      if (th == a[th] || a[th] == '-'){
        a[mf] = '-'; //or a[i]??
        a[th]= '+';
        dump(i, "after moving");
        break;
      }else if('+' == a[th] || a[th] == 'x'){
        a[mf] = '-';
        a[th] = 'x';
        dump(i, "after x");
        cout<<th<<" marked as duplicated\n";
        break;
      }
      a[i] = '-';
      
      auto evict = a[th];
      mf = th;
      a[th] = '+';
      th = evict;
      dump(i, "after evicting");
      cout<<evict<<" = evicted object\n";
    }//end of while loop, go back to for loop
  }
  dump(0, "game over");
}
/* Requirement: https://bintanvictor.wordpress.com/2018/04/07/check-array-of-0-to-n-nasdaq/
+ means the correct number is now occupying
- means vacated
x means multiple objects of this value are found
*/