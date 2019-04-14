#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep()
#include <assert.h>
#include <iostream>
using namespace std;

const size_t THREAD_CNT = 10;
int Done = 0;

//global vars not on heap:
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/* Note: error checking on pthread_X calls omitted for clarity - you
   should always check the return values in real code. */
void* ThreadEntry( void*){
  cerr<<"[thread "<<pthread_self()<<"] grabbing lock ..\n";
  
  pthread_mutex_lock( &mutex ); //need to write to shared mutable var
  cerr<<"[thread "<<pthread_self()<<"] got lock :)\n";
  const int workloops = 2;
  for( int i=1; i<=workloops; i++ ){
      printf( "[thread %d] working (%d/%d), possibly interleaved\n", pthread_self(), i, workloops );
      sleep(2); // simulate doing some costly work
  }
  Done++; // increase the count of threads that have finished their work.
  printf( "[thread %d] Done is now %d. Signaling cond.\n", pthread_self(), Done );

  // wake up the main thread (if it is sleeping) to test the value of Done  
  pthread_cond_signal( &cond ); 
  pthread_mutex_unlock( & mutex );
  return NULL;
}

int main(){
  pthread_t threads[THREAD_CNT];
  for( int t=0; t<THREAD_CNT; t++ )
    pthread_create( &threads[t], NULL, ThreadEntry, NULL );

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
}/* This simple demo is based on https://gist.github.com/rtv/4989304
g++ -g -pthread pthreadCondVar.cpp && gdb ./a.exe

q[info threads] shows 12 threads for 10 worker threads. The main thread and a last thread are out of my control.
*/
