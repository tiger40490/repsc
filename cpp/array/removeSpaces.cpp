//O(1) space, one scan
//Avoid strlen() which has O(N) cost
//Avoid unnecessary char-copying in the initial part since most strings start with non-spaces.

#include <iostream>
#include <cassert>
using namespace std;

size_t removeSpaces(char * s){ //returns # of copy operations, to be minimized
  cout<<s<<"__ is original\n";
  int cost=0, back=0;
  for(int front=back; s[front]!=0; ++front){
    if (isspace(s[front])) continue;
    if (back<front) {
      s[back] = s[front];
      cost++;
    }
    back++;
  }
  s[back]=0;
  cout<<s<<"__ is clone\n";
  return cost;
}
int main(){
  char s[]="  at  b c dd ";
  assert(6==removeSpaces(s));
  char s2[]="  at  b c dd";
  assert(6==removeSpaces(s2));
}
//requirement: https://bintanvictor.wordpress.com/2015/12/10/my-most-efficient-removespaceschar/
