/* showcasing nested class accessing enclosing class field
 * showcasing my own RAII scoped lock
 * showcasing mutex + cond wait/signal
 * showcasing std::queue
 */
#include <queue>
#include <pthread.h>
#include <unistd.h> //sleep()
#include <iostream>
using namespace std;

typedef void (*func_t)(); //func ptr
void play(){
  static int i=150;
  cout<<"Th-"<<pthread_self()<<" starting job "<<++i<<endl;
  sleep(1);
  cout<<"Th-"<<pthread_self()<<" done with job "<<i<<endl;  
}
class Tpool {
    std::queue<func_t> jobs;
    pthread_cond_t     cond; //initialized somehow
    pthread_mutex_t    mutex;
    void lock()   { pthread_mutex_lock(&mutex); }
    void unlock() { pthread_mutex_unlock(&mutex); }
    void wait()   { pthread_cond_wait(&cond, &mutex); }
    void signal() { pthread_cond_signal(&cond); }
// -------- end of skeleton given ---------
    struct ScopedLock{
      ScopedLock(Tpool* m): _m(m){ m->lock();}
      ~ScopedLock(){_m->unlock();}
      Tpool* _m;
    };
  public:
    Tpool(){
      mutex = PTHREAD_MUTEX_INITIALIZER;
      cond  = PTHREAD_COND_INITIALIZER;
    }
    void keepTaking(){ //runs on consumer thread
      for(;;){
        func_t job = NULL;
        { ScopedLock lk(this);
          while (jobs.empty()){
            cout<<"Th-"<<pthread_self()<<" [C] queue is empty ... waiting ...\n";
            wait();
            cout<<"Th-"<<pthread_self()<<" [C] woke up, will check queue, take up a job and run it..\n";
          }
          //lock released automatically when going into wait, and acquaired when waking up

          job = jobs.front(); //guaranteed non-empty
          jobs.pop();
        } //lock released
        if (job) job();
      }
    }
    void enqueue(func_t job){//runs on producer thread
      {
        ScopedLock lk(this);
        jobs.push(job);
      }

      // if this function call actually saw an empty queue, the size() call 
      // may still return a value greater than one.
      // However, another thread Must have seen size() == 1 and sent the signal!
      // If I were to put this line inside the ScopedLock block, then it's more reliable,
      // but checking size() is too lengthy for lock-holder threads.
      //
      // In java, signal() is usually called on a lock-holder thread.
      if (jobs.size() == 1) {
        cout<<"Th-"<<pthread_self()<<" [P] queue size has become 1, pulsing! \n";
        signal();
      }
    }
} tpool;
void * start(void *){
  tpool.keepTaking();
}
int main(){
  for (int i=0; i<2; ++i){
    tpool.enqueue(play);
  }
  pthread_t t1;
  pthread_create(&t1, NULL, &start, NULL);

  sleep(2); // let consumer drain the queue
  
  for (int i=0; i<3; ++i){
    sleep(2);
    tpool.enqueue(play);
  }
  void* result;
  //pthread_join(t1,&result);  
}
/* Requirement: Write the enqueue and keepTaking methods for a single thread pool.
 *
 * Given the following skeleton, write the keepTaking() method that runs in a single worker thread and repeatedly removes jobs from the queue and executes them,
 * and write the enqueue() method that is called from the main thread and adds jobs to the queue.
 */
