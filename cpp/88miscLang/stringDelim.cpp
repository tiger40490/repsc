/* 
*/
#include <cstring> //needed
#include <iostream>
#include <sstream> //getline
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

int main() {
  stringstream spaces(" a bb   x  ");
  string token;
  for(; spaces>>token;){
    cout<<token<<"|";
  }
  cout<<endl;

  stringstream csv("a,b,c,h,x"); //single delimiter char
  for(; getline(csv,token,',');){
    cout<<token<<"|";
  }
}/*
*/
