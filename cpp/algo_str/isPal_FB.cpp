/*
This simple question is really about ECT speed in the presence of 10+ unusual test cases. How do you avoid repeating yourself?

*/
#include <cassert>
#include <iostream>
using namespace std;

bool isPal(char const * s, size_t len){
  cout<<s<<" --\n";
  if (len<=1) {
    cout<<len<<" = len is 1 or less\n";  
    return true;
  }
  size_t le=0, ri=len-1;
  assert( s[len] == 0 && "last element must be null");
  
  for (;le<ri;){ // <-- this check is done only once !
    if( ! isalpha(s[le])){
      ++le;
      continue;
    }    
    if( ! isalpha(s[ri])){
      --ri;
      continue;
    }
    assert (isalpha(s[le]) && isalpha(s[ri]) &&  le<ri);
    
    if (s[le] != s[ri]) return false;
    ++le; --ri;
  }
  assert (le>=ri);
  return true;
}
bool isPal(string const & s){
  return isPal(s.c_str(), s.size());
}
int main(){
  assert(  isPal(""));
  assert(  isPal(" "));
  assert(  isPal("  "));
  assert(  isPal("   "));  
  assert(  isPal("a"));
  assert(! isPal("ab"));
  assert(  isPal("a a"));
  assert(  isPal(" aa"));
  assert(  isPal("aa "));
  assert(  isPal(" aa "));
  assert(  isPal("aba "));
}
/*Req (FB): check if a string is palindrome, ignoring any non-alphabets. O(1) space i.e. no copying please.

Interviewer can provide, if you can't recall, the util to check isLetter().
*/