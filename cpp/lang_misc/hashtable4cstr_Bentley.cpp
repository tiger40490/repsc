/* 
Q: where is the rehash functionality?

showcase: nested class
showcase: duplicate a c-string on heap, via strdup()
showcase: array of Node addresses. Actually an array of linked lists (slist), but each slist is represted as .. a Node address
showcase: allocate array of pointers then (must) initialize each to nullptr

This design uses c-str not std::string, for efficiency
*/
#include <cstring> //needed
#include <iostream>
#include <sstream> //getline
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

class CStrHashTable{
  struct Payload{ // inner class
    char const * const word; 
    int count=1; // frequency 
    Payload(char const*cstr): word(cstr){} 
  };
  struct LinkNode {
    Payload data;
    LinkNode * const next; //null indicates tail of slist.
    LinkNode(LinkNode * n, char const*cstr): 
      next(n), data(cstr) {}
  };
  const static unsigned int MULTIPLIER=31; // a popular hash multiplier for ascii strings

  //both fields below should be non-const to support rehash
  LinkNode ** bin; //note a fixed array (of pointers) won't work. Instead, "bin" points to an array, and "bin" can be reseated !
  size_t bincnt=3; //should be a prime number bigger than the expected unique word count. However, Some designs use a power-of-2

  unsigned int myhash(char const *p){ //unsigned int to ensure it never becomes negative
    unsigned int h = 0;
    const char C_STR_END = '\0' ;
    for (;*p != C_STR_END; ++p) 
      h = MULTIPLIER * h + *p;
    return h % bincnt;
  }
public:
  void incWordFrq(char const *s){ //central algo
    ss<<s<<"\t<- to be inserted.. ";
    auto const h = myhash(s);
    LinkNode * p = bin[h];
    for (; p; p=p->next){
      if (strcmp(s, p->data.word) == 0){
        ++(p->data.count);
        ss<<p->data.count<<" = new count\n";
        return;
      }
    }
    p = new LinkNode(bin[h], strdup(s));
    bin[h] = p;
    ss<<"new node created\n";
  }
  size_t dump(){
    size_t total=0;
    size_t longLists=0, longestList=0;
    for(int b=0; b<bincnt; ++b){
      size_t listLen=0;
      for (LinkNode*p=bin[b]; p; p=p->next){
        total += p->data.count;
        ++listLen;
        cout<<p->data.word<<"\t"<<p->data.count<<" in Bin # "<<b<<endl;
      }
      if (listLen >1){
        ++longLists;
        longestList = max(longestList, listLen);
      }
    }
    assert(longestList >= 3 && "test should include relatively long chains");
    assert(longLists >=2  && "test should include hash collisions in multiple bins");
    cout<<total<<" words recorded in hash table; "<<longLists<<" slists are longer than 1"<<endl;    
    return total;  
  }
  CStrHashTable(){
    bin = new LinkNode*[bincnt];
    size_t tmpBad=0;
    for(int b=0; b<bincnt; ++b){
      if (bin[b] != nullptr){ 
        ++tmpBad;
        bin[b]=nullptr; 
      }
    }
    cout<<tmpBad<<" uninitialized pointers found in the allocated array of pointers ... caused problem as tested.\n";
  }
};
int main() {
  CStrHashTable ht;
  stringstream arg("a a bb  a bb c ff dd b c dd e ff g ff h x");
  string token;
  size_t received=0;
  for(; arg>>token; ++received){
    ht.incWordFrq(token.c_str());
  }
  auto recorded = ht.dump();
  cout<<received<<" words received\n";
  assert (received == recorded);
}/* req: Without using STL containers, create a simple hashtable to hold c-strings.
In this case, we keep {word/frequency} pairs in the hashtable
This is a very simple and clean code based on Bentley's [[Programming Pearl]] P163
*/
