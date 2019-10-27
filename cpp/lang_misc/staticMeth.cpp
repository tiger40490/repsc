/*
*/
#include <iostream>
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

struct B{
  static string m2(){
    string ret = "B m2";
    cout<<ret<<endl; 
    return ret;
  }
};
struct C: public B{
  static string m2(){
    string ret = "C m2";
    cout<<ret<<endl;
    return ret;    
  }
};

int main() {
  B * ptr1 = new C;
  assert (ptr1->m2() == "B m2");
  C * ptr2 = new C;
  assert (ptr2->m2() == "C m2");
  assert (ptr2->B::m2() == "B m2");
}/*demonstrate the various flexible ways to call a static (as flexible as non-static, non-virtual..) method.
*/
