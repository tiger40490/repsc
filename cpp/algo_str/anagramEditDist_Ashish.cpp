/*
todo: use array instead of hash table
*/
#include <cassert>
#include <iostream>
#include <iomanip>
#include <unordered_map> 
using namespace std;

int editDistAnagram(string const & xx, string const & yy){
  assert(xx.size() == yy.size());
  unordered_map<char, int> frq;
  //build frq table on yy
  for (char const c: yy){
    //cout<<c<<endl;
    ++frq[c];
  }
  //go through xx and decrement from yy's table
  int hit=0;
  for (char const c: xx){
    if (frq[c] > 0){
      --frq[c];
      ++hit;
      //cout<<hit<<" hits; last char in xx is "<<c<<endl;
    }
  }
  int ret = xx.size()-hit;
  //cout<<ret<<" returned from (xx,yy)\n";
  return ret;
}
int editDistAnagram(string const & concat){
  size_t sz = concat.size();
  if (sz % 2) return -1;
  string const & xx = concat.substr(0,   sz/2);
  string const & yy = concat.substr(sz/2, sz/2);
  //cout<<xx<<" =xx; yy= "<<yy<<endl;
  return editDistAnagram(xx, yy);
}
int main(){
  int N;
  string input;
  cin>>N;
  for (int i=0; i<N; ++i){
    cin>>input;
    auto ret = editDistAnagram(input);
    cout<<ret<<endl;
  }
  return 0;
  assert(3==editDistAnagram("aaabbb"));
  assert(1==editDistAnagram("ab"));
  assert(-1==editDistAnagram("abc"));
  assert(2==editDistAnagram("mnop"));
  assert(0==editDistAnagram("xyyx"));
}
/*Req (FlowTrader): Convert string xx to yy of same length, solely by char-replacement. No insert/delete. Return minimum replacement count.
*/