#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
typedef pair<double, double> Pair;
typedef vector<Pair> Pairs;

Pairs input={{4,4}, {1,1}, {2,2}, {3,3}};

void dump(Pairs const & v, string const & headline=""){
  for(int i=0; i<v.size(); ++i){
    cout<<v[i].first<<":"<<v[i].second<<"  ";
  }cout<<endl;
}

struct MyLess: public binary_function<Pair, Pair, bool>{
  bool operator()(Pair a, Pair b) const{
    return a.first < b.first;
  }
} myLess;
int main(){
  sort(input.begin(), input.end(), myLess);
  dump(input);
}
/*requirement: https://bintanvictor.wordpress.com/2018/05/05/cva-c-iv-2/
*/