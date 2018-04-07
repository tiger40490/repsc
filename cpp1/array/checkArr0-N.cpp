#include<iostream>
#include<vector>

vector<int> v={1,2,0,2,0};
size_t const sz=v.size();
void dump(int pos, string headline=""){
  cout<<"--------"<<headline<<"------- current position = "<<pos<<endl;
  for(auto i=0; i<sz; ++i) cout<<i<<"\t";
  cout<<endl;
  for(auto i=0; i<sz; ++i) {
    if (v[i]< 0 || sz <= v[i]) cout<<(char)v[i]<<"\t";
    else cout<<v[i]<<"\t";
  }
  cout<<endl;
}
int main(){
	for (int i=0, th=a[i]/*target home*/; i<sz; ++i, th=a[i])while(1){
      if (th < 0 || sz <= th){
        dump(i, "cur is not a num");
        break; 
      }
      if (th == a[th] || a[th] == '-'){
        a[i] = '-';
        a[th]= '+';
        dump(i, "after moving");
        break;
      }else if('+' == a[th] || a[th] == 'x'){
        a[th] = 'x';
        cout<<th<<" marked as duplicated\n";
        dump(i, "after x");
        break;
      }
      a[i] = '-';
      
      auto evict = a[th];
      a[th] = '+';
      th = evict;
      cout<<evict<<" = evicted object\n";
      dump(i, "after evicting");
  }//end of while loop, go back to for loop
  dump(0, "game over");
}
/* Requirement: https://bintanvictor.wordpress.com/2018/04/07/check-array-of-0-to-n-nasdaq/
+ means the correct number is now occupying
- means vacated
x means multiple objects of this value are found
*/