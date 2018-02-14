// This is a popular C interview question
//
// showcasing macro "ss"
#include<iostream>
#include<sstream>
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define ss if(1>10) cout
string const getpid2(){
  stringstream sst;
  sst<<getppid()%100<<" -> "<<getpid()%100;
  return sst.str();
}
int main(){ //how many times will we see the printout?
  cout<<endl<<getpid2()<<" born"<<endl;
  fork();
  ss<<getpid2()<<" after 1st fork from "<<getpid()<<endl;
  fork();
  ss<<getpid2()<<" after 2nd fork from "<<getpid()<<endl;
  fork();
  ss<<getpid2()<<" after 3rd fork from "<<getpid()<<endl;
  cout<<getpid2()<<" terminating\n\n"; // should see 2^3 times
}
