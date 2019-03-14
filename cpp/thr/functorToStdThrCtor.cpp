//showcase: std::ref to produce a copyable wrapper object containing a given reference
//showcase: stateful functor object to start a thread. Rather useful.
#include <thread>
#include <iostream>
#include <unistd.h> //usleep() and sleep()
using namespace std;

struct Worker{
    Worker() : _value(0) {}
    void operator()(unsigned int input) {
      this->_value = input*input;
      long tmp=3;
      cerr<<pthread_self()<<"-Thr: doing work for "<<tmp<<" seconds ..."<<endl;
      sleep(tmp);
    }
    unsigned int get_value() {return this->_value;}
    unsigned int _value;
};

int main(){
    Worker worker;
    thread thread(std::ref(worker), 13);
    thread.join();
    unsigned int value = worker.get_value();
    cout << pthread_self()<< "-Thr: value = " << value << endl;
}/*based on https://stackoverflow.com/questions/42894629/correct-use-of-functor-for-c-stl-thread
*/
