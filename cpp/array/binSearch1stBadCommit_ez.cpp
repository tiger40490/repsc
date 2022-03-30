#include <iostream>
#include <vector>
using namespace std;

typedef int verId;
vector<short> versions={0,0,0,0,1}; //1 means bad
size_t sz=versions.size();

bool isBad(verId const v){ return versions[v]; }

verId getMid(verId a, verId b){
  return a + (b-a)/2; // guards integer overflow
}
verId get1stBad(verId le, verId ri){ // return version id of first bad version, or -1 if none in the range
  if (isBad(le)) return le;
  if ( !isBad(ri)) return -1;
  for(;;){
    if (le+1 == ri) return ri;
	verId mid = getMid(le,ri);
	if (isBad(mid))
	  ri = mid;
	else
	  le = mid;
  }
}
int main(){
  cout<<get1stBad(0, sz-1)<<" is 1st bad version id\n";
}
/*Requirement: 26 Feb first round FB IV. You are given a series of version id values, as positive integers. Once a version is bad, all subsequent versions are all bad. Please write a function to find the first bad version, within a range of versions. If none of them is bad, just return -1.

I probably spent 15 to 25 min including eyeball tests and edge cases. I was as fast as possible, but still too slow.
*/
