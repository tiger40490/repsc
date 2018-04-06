
struct MyComp: public binary_function<pair<double, double>>{
  bool operator<(pair<double, double> a, pair<double, double> b) const{
    return a.first < b.first;
  }
};
