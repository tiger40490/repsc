//showcase std::move
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
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
  Curve(Pairs && in):points(sorted(move(in))){}
  double lookup(double x){
    Pair target(x, x);
    cout<<"looking up for "<<x<<endl;
    auto li = lower_bound(points.begin(), points.end(), target);
    if (li == points.end()){
      cout<<"need to extrapolate to the right\n";
    }
    auto ui = upper_bound(points.begin(), points.end(), target);
    if (ui == points.begin()){
      cout<<"need to extrapolate to the left\n";
    }    
    cout<<li->first<<" = lower bound \n";
    cout<<ui->first<<" = upper bound \n";
    return 0;
  }
};
int main(){
  Curve c({{4,4}, {1,1}, {2,2}, {3,3}});
  dump(c.points);
  c.lookup(0.1);
  c.lookup(1);
  c.lookup(4);
  c.lookup(4.1);
}
/*requirement: https://bintanvictor.wordpress.com/2018/05/05/cva-c-iv-2/
*/