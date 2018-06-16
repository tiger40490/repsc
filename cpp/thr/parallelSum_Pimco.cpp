// showcase thread returning a value via ..join()
// [1] https://bintanvictor.wordpress.com/2018/06/16/retrieving-return-value-of-thread-function-not-really-best-practice/ discusses pthread_join() retrieving return value
// showcase ..yield()
// todo: error checking after each pthread function
#include <vector>
#include <numeric>  // std::iota
#include <pthread.h>
#include <assert.h>
#include <sched.h> //sched_yield
#include <unistd.h> //usleep()
#include <iostream>
using namespace std;
typedef size_t StartIndex;
typedef long long Result;

long long const N = 1000000;
int const M = 6; 
Result const correctAns = (1+N)*N/2;
vector<int> arr(N);
vector<Result> globalPerThrResult(M); // zeros

template<typename CT> void dump(CT const & cont) { 
    for(auto const & i: cont)        cout<<i<<endl;
}
void * run(void* arg) {
  StartIndex * ptr = static_cast<StartIndex*>(arg);
  StartIndex const startIdx = *ptr;
  delete ptr;  //we know the addr is on heap
  //cout<<"Th-"<<pthread_self()<<" : "<<startIdx<<" = startIdx\n";
  Result sum=0;
  for (int idx=startIdx; idx<N; /* last valid index is N-1*/
       idx += M){
       //cout<<"Th-"<<pthread_self()<<" : adding "<<arr[idx]<<"\n";
       sum += arr[idx];
       sched_yield(); //to see interleaving. Without this, first thread could finish the task very fast, before 2nd thread starts
  }
  //cout<<"Th-"<<pthread_self()<<" returning "<<sum<<endl;
  globalPerThrResult[startIdx] = sum;
  return new Result(sum); //must be deleted elsewhere
}
int main(){
  std::iota (arr.begin(), arr.end(), 1);  
  assert (arr[N-1] == N);
    
  vector<pthread_t> th(M);
  for (int i=0; i<M; ++i){
    pthread_create(&th[i], NULL, run, new int(i));
  }

  Result total = 0;
  void * thrResult;
  for (int i=0; i<M; ++i){
    pthread_join(th[i], &thrResult);  
    Result * subtotal = (Result*) thrResult;
    cout<<*subtotal<<" returned"<<endl;
    total += *subtotal;
	assert(globalPerThrResult[i] == *subtotal && "I prefer the array. See [1]");
    delete subtotal; //we know the addr is on heap
  }
  assert (total == correctAns);
  cout<<total<<" = grand total\n";
}
/* Requirement: 3.Implement a multithread program to sum up a large integer array [1,2,…,N].  The size of the array N is a parameter and number of the threads M is also a parameters.  Compute N=1,000,000 and M=6 in your main program.
 */
