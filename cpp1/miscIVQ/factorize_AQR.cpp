#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
vector<int> num;

size_t factorize(unsigned int bigNum){
  size_t cnt =0;
  for (int i=num.empty()? 2:num.back();   
       i<bigNum; i++)  {
    unsigned int x = bigNum/i;
    if (x < i) break;
    if (bigNum%i == 0){
      for (int j=0; j<num.size(); j++) cout << num[j] << " * ";
      cout << i << " * " << x << endl;
      cnt++;
      num.push_back(i);
      cnt += factorize(x);
      num.pop_back();
    }
  }
  //cout<<"^^^^ "<<cnt<<" formula found so far ^^^^^\bigNum";
  return cnt;
}
int main(){
  assert(8 == factorize(36));
  assert(6 == factorize(24));
  assert(3 == factorize(12));
}
/*Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
Solution from my friend Shanyou.
*/
