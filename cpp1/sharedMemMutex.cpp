#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
//#include <iostream>
using namespace std;

int const MAX=9;
int sleepMultiplier=1;

struct mapped {
  unsigned char    array[1024];
  long long        version;
  pthread_mutex_t  mutex; //embeded, not a pointer
};
void die(char const *msg) {
  perror(msg);
  exit(1);
}
mapped * create_shared_memory() {
  size_t sz = sizeof(mapped);
  pthread_mutexattr_t mutexattr;
  int rc = pthread_mutexattr_init(& mutexattr);
  if (rc != 0) die("pthread init");
  rc = pthread_mutexattr_setpshared(& mutexattr, PTHREAD_PROCESS_SHARED);
  if (rc != 0) die("pthread_mutexattr_setpshared");

  int protection = PROT_READ | PROT_WRITE; //rw access

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  auto shmem = static_cast<mapped*>(mmap(NULL, sz, protection, visibility, 0, 0));
  rc = pthread_mutex_init(& (shmem->mutex), &mutexattr);
  if (rc != 0) die("pthread_mutex_init");
  return shmem;
}
void processB(mapped * shmem){
  long long lastWrote=-1;
  for(long long i=0; i<=MAX; i+= 2){
    while (shmem->version <= lastWrote) usleep(1);
    printf("B   picked up: %s\n", shmem);
    lastWrote = i;
    char const* msg = to_string(i).c_str();
    pthread_mutex_lock(&(shmem->mutex));
    memcpy(shmem, msg, sizeof(msg));
    shmem->version=i;
    pthread_mutex_unlock(&(shmem->mutex));
    printf("B wrote: %s\n", shmem);
    usleep(1*sleepMultiplier);
  }
}
void processA(mapped * shmem){
  long long lastWrote=-1;
  for(long long i=1; i<=MAX; i+= 2){
    while (shmem->version <= lastWrote) usleep(1);
    printf(" A   picked up: %s\n", shmem);
    lastWrote = i;
    char const* msg = to_string(i).c_str();
    pthread_mutex_lock(&(shmem->mutex));
    memcpy(shmem, msg, sizeof(msg));
    shmem->version=i;
    pthread_mutex_unlock(&(shmem->mutex));
    printf(" A wrote: %s\n", shmem);
    usleep(1*sleepMultiplier);
  }
}

int main() {
  mapped* shmem = create_shared_memory();
  char const* message = "init_content";
  memcpy(shmem, message, strlen(message));

  if (fork() == 0) processA(shmem); //child
  else processB(shmem);
}
/* based on https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
g++ -std=c++0x -lpthread this_file.cpp && ./a.out
*/
