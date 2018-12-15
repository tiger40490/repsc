/* 
todo

showcase 
*/
#include <iostream>
#include <vector>
#include <set>
#include <iomanip> //setw
#include <algorithm>  //sort
#include <assert.h>
using namespace std;

int sol1(int m, int n){
  return 0;
}
int benchmark(int const m, int const n){
  int ret = m;
  for (int i=m; i<=n; ++i) ret &= i;
  cout<<ret << " {-- "<<m<<'-'<<n<<endl;
  return ret;
}
void test(pair<int,int> p){
  auto m = p.first, n=p.second;
  assert( benchmark(m,n) == sol1(m,n) ) ;
}
int main() {
  test({1,6});
}/* req: Given a continuous range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
*/
