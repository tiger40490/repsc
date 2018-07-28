#include <cassert>
#include <iostream>
#include <vector> //reqFrq
using namespace std;

string minWindow(string s, string t) {
  string const & haystack = s;
  vector<int> frq(52, 0);
  //first build the frq table
  for (auto const c: t){
    ++frq[c-'a'];
  }
  
  return "";
}
int main(){
  minWindow("bbaabccabcc", "bbc");
}
/*Req: https://bintanvictor.wordpress.com/2018/07/28/find-min-substring-containing-all-my-chars/
Given a string Haystack and a string T, find the minimum window in Haystack which contains all the characters in T in complexity O(n).
*/