//showcase initialize non-static field inline i.e. upon declaration
//showcase getting thread id from outside vs inside the target thread 
//showcase std::ref()
//showcase stateful functor object to start a thread. Rather useful.
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <vector>
#include <unistd.h> //usleep() and sleep()
using namespace std;

size_t thCnt=4;
struct Worker{
    Worker(){}
    
    void operator()(unsigned int start) {
      cout<<this_thread::get_id()<<"-Thr: updating initial value from "<<_value<<" to "<<start<<endl;
      this->_value = start;
      while(_value < 22){
        if (this->_value % thCnt == Next){ //reading Next without using any lock
          lk.lock();
          cout<<this_thread::get_id()<<"-Thr: "<<_value<<endl;
          _value += thCnt;
          Next = (Next+1)%thCnt;
          lk.unlock();
        }
        this_thread::yield();
      }
      lk.lock();
      cout<<"After while-loop, "<<this_thread::get_id()<<"-Thr: "<<_value<<endl;
      lk.unlock();
    }
    unsigned int get_value() {return this->_value;}
private:
    unsigned int _value=0;
    static mutex lk;
    static atomic<char> Next;
};
mutex Worker::lk; //must be defined outside the class to pacify linker
atomic<char> Worker::Next;
int main(){
    Worker worker[thCnt];
    vector<thread> thr;
    for (int i=0; i<thCnt; ++i){
      thr.push_back(thread(ref(worker[i]), i));
      cout<<thr[i].get_id()<<"-Thr started\n";
    }
    for (int i=0; i<thCnt; ++i){
      thr[i].join();
      cout << "per-worker final value = "<<worker[i].get_value()<<" would be wrong without ref()\n";
    }
    cout<<"Note get_id() can't return any meaningful thread id after join(). You need to save the id in advance.\n";
}/*Requirement: N threads taking turn to print integers
https://wp.me/p74oew-6Qn has more details
*/
