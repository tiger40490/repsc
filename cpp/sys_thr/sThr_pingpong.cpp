/*
todo: use rand
todo: use char as trigger
todo: use scoped lock... Scott but less flexible
todo: why the vector<Wokrer> is broken
*/
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <vector>
#include <assert.h>
#include <unistd.h> //usleep() and sleep()
using namespace std;

size_t const thCnt=3;
struct Worker{
    /*Worker(int input): trigger{input} {
        cout<<this<<" New Worker created with trigger = "<<this->trigger<<endl;
    }*/
    void operator()(int input) {
      this->trigger = input;
      while (Next != '0'){ // reading a shared mutable without lock !      
        if (0) {
          lk.lock();
          cout<<this_thread::get_id()<<"-Thr: checking  "<<trigger<<" ^ "<<Next<<endl;
          lk.unlock();
        }
        if (Next == this->trigger) {
          int next;
          //while(next == this->trigger){
              this->_value++;
              next = 65 + this->trigger % thCnt; //use rand
              //cout<<"new next == " <<next<<endl;
          //}
          lk.lock();
          cout<<this_thread::get_id()<<"-Thr: triggered, setting Next to --> "<<(char)next<<endl;
          Next = next;
          lk.unlock();
        }
        this_thread::yield();
        usleep(9*1000);
      }
      cout<<this_thread::get_id()<<"-Thr: exiting loop with "<<_value<<endl;
      return;
    }
    unsigned int get_value() {return this->_value;}
    int trigger;
    static atomic<int> Next;
private:
    size_t _value=0;
    static mutex lk;
};
mutex Worker::lk; //must be defined outside the class to pacify linker
atomic<int> Worker::Next;
int main(){
    /* why broke?
    for (int i=0; i<thCnt; ++i){
      resultCollect.push_back(Worker{});
      thr.emplace_back( ref(resultCollect.back()), tmp ); // probably broken
      cout<<thr[i].get_id()<<"-Thr started, with trigger = "<<tmp<<endl;
    }*/
    Worker worker[thCnt]; // resultCollect
    vector<thread> thr;
    for (int i=0; i<thCnt; ++i){
      int tmp = 'A' + i;
      thr.emplace_back(ref(worker[i]), tmp);
      cout<<thr[i].get_id()<<"-Thr started, with trigger = "<<tmp<<endl;
    }
    Worker::Next = 'A'; 
    usleep(99999);
    Worker::Next = '0'; //interrupt all threads
    for (int i=0; i<thCnt; ++i){
      thr[i].join();
      cout << "per-worker final value = "<<worker[i].get_value()<<"\n";
      assert (worker[i].get_value() > 1);
    }
}/*Requirement: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=39661&action=edit
*/
