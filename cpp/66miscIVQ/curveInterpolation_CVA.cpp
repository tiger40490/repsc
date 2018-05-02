//showcase std::move
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
using namespace std;
typedef pair<double, double> Pair;
typedef vector<Pair> Pairs;
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

struct Curve{
  Pairs const points;
  static Pairs & sorted(Pairs && in){
    sort(in.begin(), in.end(), myLess);
    return in;
  }
  Curve(Pairs && in):points(sorted(move(in))){
    assert(points.size() > 1 && "no interpolation");
  }
  double lookup(double x){ //what if only 1 point
  //four scenarios to handle: 1) perfect hit; 2) 2 neighbor points 3) way too high; 4) way too low; 
    cout<<"----- looking up "<<x<<endl;
    Pair target(x, x);
    auto p1 = lower_bound(points.begin(), points.end(), target);
    auto p2 = prev(p1);
    cout<<p1->first<<" = lower_bound() i.e. touchUpperBound \n";
    if (abs(p1->first-x) < 0.0000001 ){
      cout<<"perfect hit\n";      
      return p1->second;
    }else if (p1 == points.end()){
      cout<<"need to extrapolate to the right\n";
      p1 = prev(p2);
    }else if (p1 == points.begin()){
      cout<<"need to extrapolate to the left\n";
      p2 = next(p1);
    }
    cout<<p1->first<<" <-> "<<p2->first<<endl;
    return 0;
  }
};
int main(){
  Curve c({{4,4}, {1,1}, {2,2}, {3,3}});
  dump(c.points);
  c.lookup(0.1);
  c.lookup(1);
  c.lookup(1.5);
  c.lookup(4);
  c.lookup(4.1);
}
/*requirement: https://bintanvictor.wordpress.com/2018/05/05/cva-c-iv-2/
*/