#include <iostream>
#include <assert.h>
using namespace std;
bool isGood(unsigned int k){
  cout<<"\nChecking "<<k<<" ..\t";
  while(1){
    if (k%3 == 0){
      k = k/3;
      continue;
    }// now no more 3's in k
    if (k%5 == 0){
      k = k/5;
      continue;
    }
    if (k%7 == 0){
      k = k/7;
      continue;
    }
    //cout<<k<<" = k after 3 5 7\n";
    if    (k == 1) cout<<"yes";
    return k == 1;
  }
}
int main(){
  assert (!isGood(30));
  assert (isGood(15));
  for (unsigned int cand=1; cand<39; cand+=2){
    isGood(cand);
  }
}
/* Requirement(CVA): return true if k has no other factors beside 3,5 or 7. 
Full interview is described in https://bintanvictor.wordpress.com/2018/04/05/cva-c-iv-2/
*/
