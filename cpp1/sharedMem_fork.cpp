#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

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

int main() {
  char const* parent_message = "hello";  // parent process will write this message
  char const* child_message = "goodbye"; // child process will then write this one

  void* shmem = create_shared_memory(128);

  memcpy(shmem, parent_message, sizeof(parent_message));

  int pid = fork();

  if (pid == 0) {
    printf("Child picked up: %s\n", shmem);
    memcpy(shmem, child_message, sizeof(child_message));
    printf("Child wrote: %s\n", shmem);

  } else {
    printf("Parent picked up: %s\n", shmem);
    sleep(1);
    printf("After 1s, parent picked up: %s\n", shmem);
  }
}
/* based on https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
 */
