// showcase initializer for struct without ctor
#include <iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

typedef int Deadline; //deadline
struct Job {
    char id;
    Deadline dead;    // Deadline
    int profit;  // Profit if job is over before or on deadline
    friend ostream & operator<<(ostream & os, Job const & j){
      os<<"$"<<j.profit<<"  by Deadline #"<<j.dead;
      return os;
    }
};
vector<Job> arr ={{'a', 3, 30},
                  {'b', 1, 19},
                  {'c', 3, 27},
                  {'d', 1, 25},
                  {'e', 3, 15}};
size_t const sz = arr.size();
void run() {
  Deadline level=0;
  for(int i=0; i<sz; ++i) {
    if (level < arr[i].dead) level = arr[i].dead;
  }
  cout<<level<<" is longest deadline\n\n";

  for(; level >0; --level){
//    cout<<level<<" is current deadline level\n";
    int max=0;
    size_t maxWhere=arr.size();
    for(int i=0; i<arr.size(); ++i){
      if (arr[i].dead<level ) continue; //job can't wait till this long
      if (arr[i].profit > max){
        maxWhere = i;
        max = arr[i].profit;
      }
    }
    cout<<arr[maxWhere]<<" <-picked to be done by #"<<level<<endl;
    arr.erase(arr.begin()+maxWhere);
//    cout<<arr.size()<<endl;;
  }
}
int main() {
    run();
}
/*https://bintanvictor.wordpress.com/2018/03/03/simple-greedy-job-scheduler/ has my analysis
 */
