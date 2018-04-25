#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
vector<int> num;

size_t fun(int n){
  size_t cnt =0;
  int start,x,y;
  if (num.size() == 0) start = 2;
  else start = num[num.size()-1];

  for (int i=start; i<n; i++)  {
    x = n/i;
    y = n%i;
    if (x < i) break;
    if (y == 0)    {
      for (int j=0; j<num.size(); j++) cout << num[j] << "x";
      cout << i << "x" << x << endl;
      cnt++;
      num.push_back(i);
      cnt += fun(x);
      num.pop_back();
    }
  }
  //cout<<"^^^^ "<<cnt<<" formula found so far ^^^^^\n";
  return cnt;
}
int main(){
  assert(6 == fun(24));
  assert(3 == fun(12));
}
/*Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
Solution from my friend Shanyou.
*/
