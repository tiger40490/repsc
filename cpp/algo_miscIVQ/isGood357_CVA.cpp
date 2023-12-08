#include <iostream>
#include <sstream>
#include <assert.h>
using namespace std;
// Good = has no other factor beside 3,5,7
bool isGood(unsigned int k){
  stringstream sstr;
  cout<<"\nChecking "<<k<<" ..\t";
  while(1){
    if (k%3 == 0){
      sstr<<3<<' ';
      k = k/3;
      continue;
    }// now no more 3's in k
    if (k%5 == 0){
      sstr<<5<<' ';
      k = k/5;
      continue;
    }
    if (k%7 == 0){
      sstr<<7<<' ';
      k = k/7;
      continue;
    }
    //cout<<k<<" = k after 3 5 7\n";
    if    (k == 1) cout<<sstr.str();
    return k == 1;
  }
}
void findLowestGoodNumbers(size_t count, int upTo){
  int num=1; 
  for (unsigned int cand=1; cand<upTo; cand+=2){ //CANDidate
    if (isGood(cand)){
      cerr<<num++<<": "<<cand<<endl; //you can filter out stdout 
      if (num > count) return;
    }
  }  
}
int main(){
  assert (!isGood(30));
  assert (isGood(15));
  findLowestGoodNumbers(99, 99999);
}
/* Requirement(CVA): return true if k has no other factors beside 3,5 or 7. 
See https://btv-gz.dreamhosters.com/45049/all-products-of-357-cva/
*/
