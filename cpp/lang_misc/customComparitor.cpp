#include <iostream>
#include<algorithm>
#include<set>
using namespace std;

struct Job {
    string dead; //deadline
    int profit;  // Profit if job is over before or on deadline
    friend ostream & operator<<(ostream & os, Job const & j){
      os<<"$"<<j.profit<<"  by Deadline #"<<j.dead;
      return os;
    }
};
bool operator<(Job const & a, Job const& b){ return a.dead<b.dead;}
int main(){
  set<Job> jobs{{"5am", 300}, {"9am", 100}, {"7am", 200}};
  jobs.insert({"3am", 450});
  for(auto const & job: jobs){
    cout<<job<<"\n";
  }
}/*simple demo of custom comparitor function usable by std::set
*/