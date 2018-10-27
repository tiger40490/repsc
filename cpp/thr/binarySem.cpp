#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t mutex; //in global area, not allocated on heap!
int semVal = -1;

void* thread(void* arg) {
    char mode = *(char*)arg; 
    cout<<pthread_self()<<" started with arg = "<<mode<<endl;

    if (mode == 'i'){
      int errcode  = sem_post(&mutex);
      sem_getvalue(&mutex, &semVal);
      cout<<pthread_self()<<" This thread started with sem_post() without sem_wait(), current semVal = "<<semVal<<endl;
    }

    if (1){
      sem_getvalue(&mutex, &semVal);
      cout<<pthread_self()<<" current semVal = "<<semVal<<endl;

      sem_wait(&mutex);
      cout<<pthread_self()<<" Entered critical section..\n";

      sem_getvalue(&mutex, &semVal);
      cout<<pthread_self()<<" current semVal = "<<semVal<<endl<<endl;

      //critical section
      sleep(2);
    }
    cout<<pthread_self()<<" Exiting... ";
    int errcode  = sem_post(&mutex);
    cout<<pthread_self()<<" ... done with errcode ="<<errcode<< "\n";

    sem_getvalue(&mutex, &semVal);
    cout<<pthread_self()<<" current semVal = "<<semVal<<endl<<endl;
    return NULL;
}

int main()
{
    int const permitCnt=1;
    sem_init(&mutex, 0, permitCnt);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread, new char('a') ); //acquire first, but not used
    usleep(1000);
    pthread_create(&t2,NULL,thread, new char('i') );  //increment first
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_getvalue(&mutex, &semVal);
    cout<<pthread_self()<<" after all threads exited, current semVal = "<<semVal<<endl;
    assert (semVal > permitCnt);

    sem_destroy(&mutex);
    return 0;
}/*See my blog post https://wp.me/p74oew-6tz
*/
