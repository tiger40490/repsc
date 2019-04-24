/* g++ -pthread pthreadTinyTest.cpp
 */
#include <iostream>
#include <pthread.h>
using namespace std;

void *print_message(void*) {
    cout << pthread_self()<<" Threading\n";
}

int main() {
    pthread_t t1;

    pthread_create(&t1, NULL, &print_message, NULL);
    cout << pthread_self()<<" Hello\n";

    void* result;
    pthread_join(t1,&result);
    cout << pthread_self()<<" Bye\n";
}
