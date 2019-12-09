#include <thread>
#include <iostream>
#include <unistd.h> //usleep() and sleep()
using namespace std;
struct Runner{
  thread thr;
  Runner(){
    thr = thread{}; //temp object
    cout<<"no-arg ctor\n";
  }
  Runner(int unused){
    thread tmp = thread{};
    thr = move(tmp); 
    cout<<"move() needed because op= only accepts rvr\n";
  }  
  Runnner(Runner //const
          & other){
    thr = move(other.thr);
    cout<<"move() and non-const parameter needed because move(constRef) doesn't produce a rvr ! \n";
  }
};
int main(){
  Runner aa;
  Runner bb{1};
}
