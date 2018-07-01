//showcase ctor to pre-compute a field. Uses std::move
//showcase binary_function (as alt to free function) for sorting
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <assert.h>
using namespace std;
typedef pair<double, double> Pair;
typedef vector<Pair> Pairs;

template<typename K, typename V> ostream & operator<<(ostream & os, pair<K,V> const & p){
   stringstream tmp2;
   tmp2<<p.first<<":"<<p.second;
   os<<tmp2.str();
   return os;
}

template<typename T,             int min_width=4> ostream & operator<<(ostream & os, vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<setw(min_width)<<*it<<" "; }
   os<<endl;
   for(int i=0; i<c.size(); ++i){ os<<setw(min_width)<<i<<" "; }
   os<<endl;
   return os;
}

struct MyLessComparator: public binary_function<Pair, Pair, bool>{
  bool operator()(Pair a, Pair b) const{
    return a.first < b.first;
  }
} myLess;

struct Curve{
  Pairs const points;
  static Pairs & sorted(Pairs && in){
    sort(in.begin(), in.end(), myLess);
    return in; /*unsorted vector is passed in and sorted in-place and move-assigned to a field.
The field is now immutable:) This technique eliminates all wasted temp objects*/
  } 
  Curve(Pairs && in):points(sorted(move(in))){
    assert(points.size() > 1 && "interpolation impossible");
  }
  double lookup(double x){
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
  cout<<c.points;
  c.lookup(0.1); //extrapolate
  c.lookup(1);
  c.lookup(1.5);
  c.lookup(4);
  c.lookup(4.1); //extrapolate
}
/*requirement: https://bintanvictor.wordpress.com/2018/05/05/cva-c-iv-2/ piecewise linear interpolation
This question is not tough algorithm but syntax
*/