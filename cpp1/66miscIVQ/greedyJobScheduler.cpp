// showcase initializer for struct without ctor
// showcase sort with global operator<()
#include <iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

typedef int Deadline;
struct Job {
    char id;
    Deadline dead;
    int profit;  // Profit if job is over before or on deadline
    friend ostream & operator<<(ostream & os, Job const & j){
      os<<"$"<<j.profit<<"  by Deadline #"<<j.dead;
      return os;
    }
};
bool operator<(Job const & a, Job const& b){ return a.dead>b.dead;}
vector<Job> arr ={{'a', 2, 100},
                  {'b', 1, 19},
                  {'c', 2, 27},
                  {'d', 1, 25},
                  {'e', 4, 45},
                  {'f', 4, 29},
                  {'g', 2, 26},
                  {'z', 3, 15}};
size_t const sz = arr.size();
void run() {
  sort(arr.begin(), arr.end());

  for(Deadline level=arr[0].dead; level >0; --level){
    size_t mx=0;
    for(int i=0; i<arr.size(); ++i){
      if (arr[i].dead<level ) break; //all subsequent jobs can't wait till this long
      if (arr[i].profit > arr[mx].profit) mx = i;
    }
    cout<<arr[mx]<<" <-picked to be done by #"<<level<<endl;
    arr.erase(arr.begin()+mx);
  }
}
int main() {
    run();
}
/*https://bintanvictor.wordpress.com/2018/03/03/simple-greedy-job-scheduler/ has my analysis
 */
