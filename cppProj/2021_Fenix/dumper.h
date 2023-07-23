#pragma once
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

template<typename K, typename V> std::ostream & operator<<(std::ostream & os, std::pair<K,V> const & p){
   os<<p.first<<","<<p.second;
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
/*
template<  template<typename,class> class Container, 
typename V, class Alloc, int min_width=8>
std::ostream& operator<<(std::ostream& os, Container<V, Alloc> const& c){
   // takes any (container or otherwise) template having 2 templ params, but not maps (4) or sets (3)
   for(auto const & it : c){ os<<std::setw(min_width)<<it<<" "; }
   os<<std::endl;
   //for(int i=0; i<c.size(); ++i){ os<<std::setw(min_width)<<i<<" "; }
   //os<<std::endl;
   return os;
}*/
template<typename T,             int min_width=8> std::ostream & operator<<( std::ostream & os, std::vector<T> const & c){
   for(auto it = c.begin(); it != c.end(); ++it){ os<<std::setw(min_width)<<*it<<" "; }
   os<<std::endl;
   for(int i=0; i<c.size(); ++i){ os<<std::setw(min_width)<<i<<" "; }
   os<<std::endl;
   return os;
}
template<typename T,             int min_width=2> std::ostream & operator<<( std::ostream & os, std::list<T> const & c){
   for(auto const & it: c){ os<<std::setw(min_width)<<it<<" "; }
   os<<std::endl;
   return os;
}