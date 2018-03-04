#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <string>
#include <unistd.h>
using namespace std;

void* shmem;
int const MAX=9;
int sleepMultiplier=1;
void* create_shared_memory(size_t size) {
  int protection = PROT_READ | PROT_WRITE; //rw access

  // The buffer will be shared (meaning other processes can access it), but
  // anonymous (meaning third-party processes cannot obtain an address for it),
  // so only this process and its children will be able to use it:
  int visibility = MAP_ANONYMOUS | MAP_SHARED;

  // The remaining parameters to `mmap()` are not important for this use case,
  // but the manpage for `mmap` explains their purpose.
  return mmap(NULL, size, protection, visibility, 0, 0);
}
void processB(){
  for(long long i=0; i<MAX; i+= 2){
    printf("B picked up: %s\n", shmem);
    char const* msg = to_string(i).c_str();
    memcpy(shmem, msg, sizeof(msg));
    printf("B wrote: %s\n", shmem);
    usleep(3*sleepMultiplier);
  }
}
void processA(){
  for(long long i=1; i<MAX; i+= 2){
    printf(" A picked up: %s\n", shmem);
    char const* msg = to_string(i).c_str();
    memcpy(shmem, msg, sizeof(msg));
    printf(" A wrote: %s\n", shmem);
    usleep(2*sleepMultiplier);
  }
}

int main() {
  shmem = create_shared_memory(128);
  char const* message = "initial_content";
  memcpy(shmem, message, sizeof(message));

  int pid = fork();

  if (pid == 0) processA(); //child
  else processB();
}
/* based on https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
*/
