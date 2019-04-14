#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //usleep() and sleep()
#include <iostream>
using namespace std;

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

int  count = 0;
#define COUNT_DONE  10
#define COUNT_HALT1  3
#define COUNT_HALT2  6

// Write numbers 1-3 and 8-10 as permitted by functionCount2()
void *functionCount1(void*)
{
   cout<<"entering f1"<<endl;
   for(;;)
   {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock( &count_mutex );
      cout<<"f1 grabbed:)"<<endl;

      // Wait while functionCount2() operates on count
      // mutex unlocked if condition varialbe in functionCount2() signaled.
      cout<<"f1 entering wait, releasing lock"<<endl;
      pthread_cond_wait( &condition_var, &count_mutex );
      cout<<"f1 wait returned, lock grabbed"<<endl;
      count++;
      printf("Counter value functionCount_1: %d\n",count);

      pthread_mutex_unlock( &count_mutex );
      cout<<"f1 released:) but this log msg may show up late"<<endl;

      if(count >= COUNT_DONE) return(NULL);
    }
}

// Write numbers 4-7
void *functionCount2(void*dummy)
{
    for(;;)
    {
      pthread_mutex_lock( &count_mutex );
      cout<<"f2 grabbed:)"<<endl;

       if( count < COUNT_HALT1 || count > COUNT_HALT2 )
       {
          // Condition of if statement has been met. 
          // Signal to free waiting thread by freeing the mutex.
          // Note: functionCount1() is now permitted to modify "count".
          pthread_cond_signal( &condition_var );
          //cout<<"f2 done notifying, still holding lock"<<endl;
       }
       else
       {
          count++;
          printf("Counter value functionCount_2: %d\n",count);
       }

       cout<<"f2 releasing (waiting thread may steal the log stream now)..."<<endl;
       pthread_mutex_unlock( &count_mutex );
       cout<<"f2 released:) but this log msg may show up late"<<endl;
       sched_yield();

       if(count >= COUNT_DONE) return(NULL);
    }
}

main()
{
   struct timespec ts;
   ts.tv_sec = 0;
   ts.tv_nsec= 1;
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &functionCount1, NULL);

   usleep(1); //without this thread2 would start first, though the start sequence doesn't affect biz logic. Note pthread_yield isn't enough to postpone thread2

   pthread_create( &thread2, NULL, &functionCount2, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);
   printf("Final count: %d\n",count);
   exit(0);
}
