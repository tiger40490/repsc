/* 
todo: try the bitset::flip() method
*/
#include <iostream>
#include <assert.h>
#include <bitset>
using namespace std;

int const SZ=22;
int solve(int orig){
  if (orig == 0) return 0;
  auto bset = bitset<SZ>(orig);
  //string binary = bset.to_string(); //to binary
  cout<<bset.to_string()<<"\n";
  int i=SZ-1;
  for (; i>=0; --i){
    cout<<bset[i]<<endl;
    if (bset[i]){ 
      cout<<i<<" <-- is highest 1-bit position\n";
      break;
    }
  }
  assert (i >= 0) ;
  for (; i>=0; --i){
    cout<<bset[i]<<endl;
    bset[i] = ! bset[i];
  }
  auto ret = bset.to_ulong();
  cout<<ret<<" returned as complement\n";
  return ret;
}

int main(){
  solve(50);
  return 0;
  string binary = bitset<SZ>(1048576).to_string(); //to binary
  cout<<binary<<"\n";

  unsigned long decimal = bitset<SZ>(binary).to_ulong();
  cout<<decimal<<"\n";
}/* req: given a non-negative int, flip all bits starting from its highest 1-bit. Return the new int.
*/
