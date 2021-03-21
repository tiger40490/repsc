/*
showcase: uniform random int
showcase: wrap cout in lock guard to prevent interleaved printing
showcase: friend function
showcase: mutex as private static field 
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

bool isVerbose = true;
bool isTestingRace = true;
size_t const thCnt=isTestingRace? 5:3;
size_t const limit=isTestingRace? 99:5;
int randomInt(int min=0, int max=thCnt-1){ 
// https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
  static std::mt19937 rng{ std::random_device{}() };  // create temp random_device and call its operator()
  static std::uniform_int_distribution<int> uniform(min,max);
  return uniform(rng);
}

struct Worker{
    Worker(trigger_t input): myTrigger{input} {
        if (isVerbose){   
          lk.lock();
          cout<<this<<" (possibly same addr reused, on stack!) New Worker created with myTrigger = "<<this->myTrigger<<endl;
          lk.unlock();
        }
    }
    void operator()(trigger_t input /*not in use*/) {
      thread::id const tid = this_thread::get_id();
      //cout<<tid<<"-Thr's driver (in verctor) has address = "<<this<<endl;
      while (NoticeBoard != '0'){ // reading a shared mutable without lock !
        if (isVerbose && !isTestingRace) {
          lk.lock();
          cout<<tid<<"-Thr: checking  "<<myTrigger<<" ^ "<<NoticeBoard<<endl;
          lk.unlock();
        }
        if (NoticeBoard == this->myTrigger) {
          trigger_t next=this->myTrigger;
          if (limit == ++_value) {
              next = '0';
          }else while(next == this->myTrigger)          {
              next = 'A' + randomInt(); // a random character chosen from 'A' to the highest
          }
          lk.lock();
          cout<<tid<<"-Thr: " <<NoticeBoard<<" --> "<<next<<endl;
          if (!isTestingRace) assert (NoticeBoard != '0');
          NoticeBoard = next;
          assert (NoticeBoard != this->myTrigger);
          lk.unlock();
        }
        this_thread::yield();
      } //end of while
      if (isVerbose){
        lk.lock();
        cout<<tid<<"-Thr: exiting loop with "<<_value<<endl;
        lk.unlock();
      }
      return;
    }
    unsigned int get_value() {return this->_value;}
    friend int main();
    static mutex lk;
private:
    static atomic<trigger_t> NoticeBoard;
    const trigger_t myTrigger;
    size_t _value=0;
};

mutex Worker::lk; //must be defined outside the class to pacify linker
atomic<trigger_t> Worker::NoticeBoard;

int main(){
    //Worker worker[thCnt]; // proven working, but use no-arg ctor
    vector<Worker> worker; worker.reserve(thCnt);
    vector<thread> thr;
    for (int i=0; i<thCnt; ++i){
      trigger_t tmp = 'A' + i;
      worker.push_back(Worker{tmp});
      thr.emplace_back(ref(worker[i]), tmp);
      Worker::lk.lock();
      cout<<thr[i].get_id()<<"-Thr started, with myTrigger = "<<tmp<<endl;
      Worker::lk.unlock();
    }
    Worker::NoticeBoard = 'A' + randomInt(); //kickstart
    if (isTestingRace){
      usleep(1000); 
      cout<<"inject 0..\n"<<endl;
      Worker::NoticeBoard = '0'; //Unsafe practice, deadlock-prone, esp. when thCnt is high
    }
    for (int i=0; i<thCnt; ++i){
      thr[i].join();
      cout << i<<"-th worker final value = "<<worker[i].get_value()<<"\n";
      if (!isTestingRace) assert (worker[i].get_value() > 1);
    }
}/*Requirement: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=39661&action=edit
*/
