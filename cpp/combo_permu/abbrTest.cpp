#define DEBUG
#include "abbr_ascendRecursive.h"

int main() {
  string tmp = "abcd";
  deque<char> v(tmp.begin(), tmp.end());
  deque<deque<char> > ret = recurs(v);
#ifndef DEBUG
  show(ret);
#endif
  set<deque<char> > unique(ret.begin(), ret.end());
  cout<<calls<<"  calls to the recursive funcion to generate "<<ret.size()<<" abbreviations. Including the empty, unique count = "<<unique.size()<<endl;
}
