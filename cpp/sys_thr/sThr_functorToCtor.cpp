//showcase: std::ref to produce a copyable wrapper object containing a given reference
//showcase: main thread to retrieve worker function return value
//showcase: stateful functor object to start a thread. Rather useful.
//showcase string literal concat a string object
#include <thread>
#include <iostream>
#include <unistd.h> //usleep() and sleep()
using namespace std;
////////// Experiment 1:
void demoFuncWithArg(string const & str){
  cerr<<pthread_self()<<"-Thr: doing work for "+str+", printed from demoFuncWithArg\n";
}
template<typename FuncT, typename ParamT>
struct AdapterWrapperWorker{
  AdapterWrapperWorker(FuncT f, ParamT& p): 
    funcPtr(f), 
    param(p){}
    
  //this operator conforms to the shortest, simplest std::thread ctor
  void operator()(){ this->funcPtr(param); }
private:
  FuncT funcPtr;
  ParamT param;
};
////////// Experiment 2:
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
    typedef void (*MyFunctor)(string const&);
    AdapterWrapperWorker<MyFunctor, string const>  worker2(demoFuncWithArg, "testing");
    thread thread2(worker2);
    thread2.join();
  
    Worker worker3;
    thread thread3(std::ref(worker3), 13);
    thread3.join();
    unsigned int value = worker3.get_value();
    cout << pthread_self()<< "-Thr: value = " << value << endl;
}/*based on https://stackoverflow.com/questions/42894629/correct-use-of-functor-for-c-stl-thread
*/
