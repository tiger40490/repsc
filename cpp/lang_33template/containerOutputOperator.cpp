//todo: use enable_if or something else to disallow std::string
//showcase: templ-templ param
//Showcase: non-dummy-type template param min_width.
//showcase conditional compilation based on -std=c++17
// Note body of map ^ vector dumpers can be identical, except some optional features.
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <vector>
//
// Below is minimum code block for copy-paste.
#include <iostream>
#include <iomanip>
#define Map std::unordered_map
#define Set std::set
#define ss if(1>0)std::cout //to mass-disable cout before uploading to hacker rank
//using namespace std;

template<typename K, typename V> std::ostream & operator<<(std::ostream & os, std::pair<K,V> const & p){
   os<<p.first<<":"<<p.second;
   return os;
}
template<typename K, typename V, int min_width=8> std::ostream & operator<<(std::ostream & os,  Map<K,V> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<std::setw(min_width)<<*it<<" "; }
   os<<std::endl;
   return os;
}
template<typename T,             int min_width=2> std::ostream & operator<<(std::ostream & os, Set<T> const & c){
   for(auto const & it: c){ os<<std::setw(min_width)<<it<<" "; }
   os<<std::endl;
   return os;
}
template<  template<typename,class> class Container, 
typename V, class Alloc, int min_width=8>
std::ostream& operator<<(std::ostream& os, Container<V, Alloc> const& c){
   // takes any (container or otherwise) template having 2 templ params, but not maps (4) or sets (3)
   for(auto const & it : c){ os<<std::setw(min_width)<<it<<" "; }
   os<<std::endl;
   for(int i=0; i<c.size(); ++i){ os<<std::setw(min_width)<<i<<" "; }
   os<<std::endl;
   return os;
}
// The above template affects std::string. You may have to use cout<<std::string("abc").c_str()
//template<> std::ostream& operator<< <std::__cxx11::basic_string, char, char_traits<char> >(std::ostream& os, string const&) = delete; //Not effective :( because even deleted template-specialization can cause ambiguous overload under c++17

int main(){
  std::list<double> li={3.1, 5,2,9};
  Set<short> myset={1, 2, 42, 5};
#if (__cplusplus >= 201703L)
  std::vector<float> vec={3.5, 1.9, 0.8};
#else  
  std::vector<std::string> vec={"dabao", "meimei", "princess"}; //works under g++ -std=c++14 but not c++17
#endif
  Map<int, bool> tm={{11,true}, {22,false}};
  ss<<vec<<tm;
  ss<<" <-- vector and map; list and set -->\n";
  ss<<li<<myset;
  ss<<__cplusplus <<" = __cplusplus \n";
  //ss<<std::string("dummy"); // broken 
}
