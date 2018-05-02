#include <iostream>
#include <cassert>
using namespace std;
//Avoid strlen() which has O(N) cost
//Avoid unnecessary char-copying in the initial part since most strings start with non-spaces.

void removeSpaces(char * s){
  int i=0;
  for(; !isspace(s[i]); ++i){
    if (s[i] == 0) return;
  }

  assert(isspace(s[i]) &&
"This should be the first space. Before this position, we have saved unnecessary char-copying");

  for(int front=i; s[front]!=0; ++front){
    if (isspace(s[front])) continue;
      s[i++] = s[front];
  }
  s[i]=0;
}
int main(){
  char s[]="  at  b c dd ";
  cout<<s<<"__\n";
  removeSpaces(s);
  cout<<s<<"__\n";
}
// https://bintanvictor.wordpress.com/2015/12/10/my-most-efficient-removespaceschar/
