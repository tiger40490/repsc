/*
todo: abbc
showcase initializing a treeset of deque of char, from a another container
*/
#define DEBUG //referenced by header
#include "abbr_ascendRecursive.h"
using namespace std;

int main() {
  outer<deque<char> > ret = generateAsc("aac");
  set<deque<char> > unique(ret.begin(), ret.end());
  cout<<calls<<"  calls to the recursive funcion to generate "<<ret.size()<<" abbreviations. Including the empty, unique count = "<<unique.size()<<endl;
  assert(ret.size() == unique.size());
}
