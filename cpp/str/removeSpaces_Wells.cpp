//one-scan, 2-ptr algorithm in O(1) space
//Avoid strlen() which has O(N) cost
//Avoid unnecessary char-copying in the initial part since many realistic strings start with non-space.

#include <iostream>
#include <cassert>
using namespace std;

size_t removeSpaces(char * s){ //returns # of copy operations, to be minimized
  cout<<s<<"__ is original\n";
  int cost=0, back=0, front=0; //front can be declared in for-loop header but in speed coding this way is simpler
  for (; s[front]; ++front){
    if (isspace(s[front])) continue;
    if (back < front){
        s[back] = s[front];
        ++cost;
    }
    ++back;
  }
  s[back]=0; //in coding tests, 0 is faster to type
  cout<<s<<"__ is afterwards\n";
  return cost;
}
int main(){
  char s[]="  at  b c dd ";
  assert(6==removeSpaces(s));
  char s2[]="at  b c dd";
  assert(4==removeSpaces(s2));
}
//requirement: https://bintanvictor.wordpress.com/2015/12/10/my-most-efficient-removespaceschar/
