#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
vector<int> num;

size_t factorize(unsigned int bigNum){
  size_t cnt =0;
  unsigned int start,x,y;
  start = num.empty()? 2: num.back();

  for (int i=start; i<bigNum; i++)  {
    x = bigNum/i;
    y = bigNum%i;
    if (x < i) break;
    if (y == 0)    {
      for (int j=0; j<num.size(); j++) cout << num[j] << "x";
      cout << i << "x" << x << endl;
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
  assert(6 == factorize(24));
  assert(3 == factorize(12));
}
/*Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
Solution from my friend Shanyou.
*/
