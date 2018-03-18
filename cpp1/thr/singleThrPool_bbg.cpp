/* showcasing nested class
 * showcasing my own RAII soped lock
 *
 * No main(). Compile with -c. Unable to test
 */
#include <queue>
#include <pthread.h>
typedef void (*func_t)(); //func ptr

class Data {
    std::queue<func_t> jobs;
    pthread_cond_t     cond; //initialized somehow
    pthread_mutex_t    mutex;
    void lock()   { pthread_mutex_lock(&mutex); }
    void unlock() { pthread_mutex_unlock(&mutex); }
    void wait()   { pthread_cond_wait(&cond, &mutex); }
    void signal() { pthread_cond_signal(&cond); }
  public:
    Data();
// -------- end of skeleton given ---------
    struct ScopedLock{
      ScopedLock(Data* m): _m(m){ m->lock();}
      ~ScopedLock(){_m->unlock();}
      Data* _m;
    };
    void run(){
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
    void enqueue(func_t job){
      {
        ScopedLock lk(this);
        jobs.push(job);
      }

      // if this function call actually saw an empty queue, the size() may still return a non-one
      // However, another thread Must have seen size() == 1 and sent the signal!
      // If I were to put this line inside the ScopedLock block, then it's more reliable,
      // but checking size() is too lengthy for lock-holder threads.
      //
      // In java, signal() is usually called on a lock-holder thread.
      if (jobs.size() == 1) signal();
    }
};
/* Write the enqueue and dequeue methods for a single thread pool.
 *
 * Given the following skeleton, write the run() method that runs in a single worker thread and repeatedly removes jobs from the queue and executes them,
 * and write the enqueue() method that is called from the main thread and adds jobs to the queue.
 */
