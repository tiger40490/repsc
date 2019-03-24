/* 
todo: tighten the const arond char*

showcase: allocate array of pointers then (must) initialize each to nullptr
showcase: nested class
showcase: duplicate a c-string on heap
showcase: array of Node addresses. Actually an array of linked lists (slist), but each slist is represted as .. a Node address

This design uses c-str not std::string, for efficiency
*/
#include <cstring> //needed
#include <iostream>
#include <sstream> //getline
#include <assert.h>
#define ss if(1>0)cout //to mass-disable cout before uploading to hacker rank
using namespace std;

class CStrHashTable{
  struct Payload{ 
    char const * const word; 
    int count=1;
    Payload(char const*cstr): word(cstr){} 
  };
  struct LinkNode {
    Payload data;
    LinkNode * const next;
    LinkNode(LinkNode * n, char const*cstr): 
      next(n), data(cstr) {}
  };
  const static unsigned int MULTIPLIER=31; // a popular value for ascii strings

  //both fields below should be non-const to support rehash
  LinkNode ** bin; //note an fixed array of pointers can't grow
  size_t bincnt=3; //should be a prime number bigger than the expected unique word count. Some designs use a power-of-2

  unsigned int myhash(char const *p){ //unsigned int to ensure it never becomes negative
    unsigned int h = 0;
    for (;*p != '\0'; ++p) 
      h = MULTIPLIER * h + *p;
    return h % bincnt;
  }
public:
  void incword(char const *s){ //central algo
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
    ht.incword(token.c_str());
  }
  auto recorded = ht.dump();
  cout<<received<<" words received\n";
  assert (received == recorded);
}/* req: Without using STL containers, create a simple hashtable to hold c-strings
This is a very simple and clean code based on Bentley's [[Programming Pearl]] P163
*/
