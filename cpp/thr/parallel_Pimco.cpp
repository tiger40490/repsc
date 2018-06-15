// showcase thread returning a value via join()
#include <vector>
#include <numeric>  // std::iota
#include <pthread.h>
#include <assert.h>
#include <unistd.h> //usleep()
#include <iostream>
using namespace std;
typedef int StartIndex;
//typedef int Result;

long long const N = 100;
int const M = 6; 
long long const correctAns = (1+N)*N/2;
vector<int> arr(N);
//vector<Result> results(M); // all zeros
template<typename CT> void dump(CT const & cont) { 
    for(auto const & i: cont)        cout<<i<<endl;
}
void * run(void* arg) {
  StartIndex * ptr = static_cast<StartIndex*>(arg);
  StartIndex const startIdx = *ptr;
  delete ptr;
  //cout<<"Th-"<<pthread_self()<<" : "<<startIdx<<" = startIdx\n";
  long long sum=0;
  for (int idx=startIdx; idx<N; /* last valid index is N-1*/
       idx += M){
       //cout<<"Th-"<<pthread_self()<<" : adding "<<arr[idx]<<"\n";
       sum += arr[idx];
       usleep(1);
  }
  //results[startIdx] = sum;
  //cout<<"Th-"<<pthread_self()<<" returning "<<sum<<endl;
  return new int(sum);
}
int main(){
  std::iota (arr.begin(), arr.end(), 1);  
  assert (arr[N-1] == N);
  
  vector<StartIndex> starts(M); 
  std::iota (starts.begin(), starts.end(), 0);  
  //dump(starts);
  
  vector<pthread_t> th(M);
  for (int i=0; i<M; ++i){
    pthread_create(&th[i], NULL, &run, new int(i));
  }

  long long total = 0;
  void * thrResult;
  for (int i=0; i<M; ++i){
    pthread_join(th[i], &thrResult);  
    int * subtotal = (int*) thrResult;
    //cout<<*subtotal<<" returned"<<endl;
    total += *subtotal; //results[i];
    delete subtotal; //we know the addr is on heap
  }
  assert (total == correctAns);
  cout<<total<<" = grand total\n";
}
/* Requirement: 3.	Implement a multithread program to sum up a large integer array [1,2,…,N].  The size of the array N is a parameter and number of the threads M is also a parameters.  Compute N=1,000,000 and M=6 in your main program.
 */
