/*
todo: trigger should be a const field
showcase: uniform random int
showcase: wrap cout in lock guard to prevent interleaved printing
*/
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <vector>
#include <assert.h>
#include <unistd.h> //usleep() and sleep()
#include <random>
using namespace std;
typedef char trigger_t; 

size_t const thCnt=3, limit=9;
int randomInt(int min=0, int max=thCnt){ 
// https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
  static std::mt19937 rng{ std::random_device{}() };  // create temp random_device and call its operator()
  static std::uniform_int_distribution<int> uniform(min,max);
  return uniform(rng);
}
struct Worker{
    /*Worker(int input): trigger{input} {
        cout<<this<<" New Worker created with trigger = "<<this->trigger<<endl;
    }*/
    void operator()(trigger_t input) {
      this->trigger = input;
      thread::id const tid = this_thread::get_id();
      while (NoticeBoard != '0'){ // reading a shared mutable without lock !
        if (0) {
          lk.lock();
          cout<<tid<<"-Thr: checking  "<<trigger<<" ^ "<<NoticeBoard<<endl;
          lk.unlock();
        }
        if (NoticeBoard == this->trigger) {
          trigger_t next=this->trigger;
          if (limit == ++_value) {
              next = '0';
          }else while(next == this->trigger)
          {
              next = 'A' + randomInt() % thCnt;
          }
          lk.lock();
          cout<<tid<<"-Thr: " <<NoticeBoard<<" --> "<<next<<endl;
          assert (NoticeBoard != '0');
          NoticeBoard = next;
          assert (NoticeBoard != this->trigger);
          lk.unlock();
        }
        this_thread::yield();
      } //end of while
      if (0){
        lk.lock();
        cout<<tid<<"-Thr: exiting loop with "<<_value<<endl;
        lk.unlock();
      }
      return;
    }
    unsigned int get_value() {return this->_value;}
    int trigger;
    static atomic<trigger_t> NoticeBoard;
private:
    size_t _value=0;
    static mutex lk;
};
mutex Worker::lk; //must be defined outside the class to pacify linker
atomic<trigger_t> Worker::NoticeBoard;
int main(){
    //Worker worker[thCnt]; // proven working, but only for no-arg ctor
    vector<Worker> worker; worker.reserve(thCnt);
    vector<thread> thr;
    for (int i=0; i<thCnt; ++i){
      trigger_t tmp = 'A' + i;
      worker.push_back(Worker{});
      thr.emplace_back(ref(worker[i]), tmp);
      cout<<thr[i].get_id()<<"-Thr started, with trigger = "<<tmp<<endl;
    }
    Worker::NoticeBoard = 'A'; //kickstart
    //usleep(100); Worker::NoticeBoard = '0'; //race condition risk higher with thCnt
    for (int i=0; i<thCnt; ++i){
      thr[i].join();
      cout << i<<"-th worker final value = "<<worker[i].get_value()<<"\n";
      assert (worker[i].get_value() > 1);
    }
}/*Requirement: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=39661&action=edit
*/
