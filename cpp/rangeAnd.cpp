/* 
todo: more tests
showcase 
*/
#include <iostream>
//#include <vector>
//#include <set>
//#include <algorithm>  //sort
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;
int roundUp(int v){// compute the next highest power of 2 of 32-bit v, possibly v itself
  ss<<v<<" rounding up to ";
  assert (v > 0 && "0 is not supported");
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  ss<<v<<endl;
  return v;
}
int sol1(int m, int n){
  if (m==0) return 0;
  int ret = 0;
  for(auto mask = roundUp(n); mask>0; mask/=2){
    ss<<mask<<" is the new test mask\n";
    auto rounded = m & mask;
    if  (rounded != (n & mask)) break;
    if  (rounded) {
      ss<<mask<<"+\n";
      ret += mask;
    }
  }
  return ret;
}
int benchmark(int const m, int const n){
  int ret = m;
  for (int i=m; i<=n; ++i) ret &= i;
  cout<<ret << " {-- "<<m<<'-'<<n<<endl;
  return ret;
}
void test(pair<int,int> p){
  auto m = p.first, n=p.second;
  auto actual = sol1(m,n), exp = benchmark(m,n);
  assert(exp == actual);
}
int main() {
  test({17102, 17120});
  test({12,14});
  test({11,15});
  //edge cases:
  test({1,255});
  test({2,255});
  test({1,2});
  test({4,4});
  test({8,15});
  test({8,16});
  test({0,29});
  test({0,128});
}/* req: Given a continuous range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
https://wp.me/p74oew-6Ah
*/
