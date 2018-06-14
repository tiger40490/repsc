/* showcasing nested class
 * showcasing my own RAII scoped lock
 *
 * Dummy main(). Unable to test
 */
#include <queue>
#include <pthread.h>
typedef void (*func_t)(); //func ptr

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
    void dequeue(){ //runs on consumer thread
      for(;;){
        func_t job = NULL;
        { ScopedLock lk(this);
          while (jobs.empty()) wait();
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
      if (jobs.size() == 1) signal();
    }
};
int main(){
}
/* Requirement: Write the enqueue and dequeue methods for a single thread pool.
 *
 * Given the following skeleton, write the dequeue() method that runs in a single worker thread and repeatedly removes jobs from the queue and executes them,
 * and write the enqueue() method that is called from the main thread and adds jobs to the queue.
 */
