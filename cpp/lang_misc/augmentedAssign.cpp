/*
same as in python, the rhs of augmented assignment is a single expression
*/
#include <iostream>
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

int main() {
  string token="str1";
  token += string(" suffix1") + " suff2"; //concise .. in speed coding 
  cout<<token<<endl;
  
  int age=3;
  age *= 2+5;
  assert (age == 3*7);
  cout<<age<<endl;
}/*
*/
