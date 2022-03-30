/* g++ -pthread pthreadCondVar.cpp
This simple demo is based on https://gist.github.com/rtv/4989304
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep()
#include <assert.h>
#include <iostream>
using namespace std;

const size_t THREAD_CNT = 4;
int Done = 0;

//global vars not on heap:
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/* Note: error checking on pthread_X calls omitted for clarity - you
   should always check the return values in real code. */

/* Note: passing the thread id via a void pointer is cheap and easy,
 * but the code assumes pointers and long ints are the same size
 * (probably 64bits), which is a little hacky. */

void* ThreadEntry( void* id ){
  assert(sizeof(void*) == sizeof(long long));
  const int myid = (long long)id; // force the pointer to be a long integer
  
  const int workloops = 3;
  for( int i=1; i<=workloops; i++ ){
      printf( "[thread %d] working (%d/%d), possibly interleaved\n", myid, i, workloops );
      sleep(1); // simulate doing some costly work
  }
  pthread_mutex_lock( &mutex ); //need to write to shared mutable var
  Done++; // increase the count of threads that have finished their work.
  printf( "[thread %d] Done is now %d. Signaling cond.\n", myid, Done );

  // wake up the main thread (if it is sleeping) to test the value of Done  
  pthread_cond_signal( &cond ); 
  pthread_mutex_unlock( & mutex );
  return NULL;
}

int main( int argc, char** argv ){
  pthread_t threads[THREAD_CNT];
  for( int t=0; t<THREAD_CNT; t++ )
    pthread_create( &threads[t], NULL, ThreadEntry, (void*)(long long)t );

  pthread_mutex_lock( &mutex ); //needed to read Done and use the cond var
  while( Done < THREAD_CNT ){
      printf( "[thread main] Done is %d which is < %d so waiting on cond\n", 
	      Done, (int)THREAD_CNT );
      
      /* block this thread until another thread signals cond. While
	 blocked, the mutex is released, then re-aquired before this
	 thread is woken up and the call returns. */ 
      pthread_cond_wait( & cond, & mutex ); 
      cout<<"[thread main] wake - cond was signaled.\n"; 
  }
  printf( "[thread main] Done == %d so everyone is Done\n", (int)THREAD_CNT );
  pthread_mutex_unlock( & mutex );
}