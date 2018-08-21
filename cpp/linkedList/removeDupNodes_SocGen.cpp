/*
todo: avoid memory leak

showcase switch-case + command line arg to specify a single test case. Below is a composite command to run multiple tests:
  g++ ez_removeBadNodes_Flex.cpp && ./a.exe 0 && ./a.exe p && ./a.exe a && ./a.exe 1
*/
#include <iostream>
#include <cassert>
#include <memory>
using namespace std;
struct Node{
  size_t data; Node * next;
  Node (size_t payload, Node* n=nullptr): data(payload), next(n){}
} _10(10), 
  _9(99, &_10),
  _8(38, &_9),
  _7(77, &_8),
  _6(26, &_7),
  _5(55, &_6),
  _4(84, &_5),
  _3(63, &_4),
  _2(42, &_3),
  _1(11, &_2);
Node * head = &_1;
size_t dump(Node *h){
  size_t ret = 0;
  for (; h; h=h->next){
    cerr<<h->data<<"->";
    ++ret;
  }
  cerr<<"nullptr\n";
  return ret;
}
Node* solution1(Node* listHead){ //
  int seen[1001]={0}; //list payloads always between 0 and 1000
  int cnt=0;
  auto i=listHead, j=listHead->next; //two pointers needed
  seen[i->data]=1; //code smell
  for(;;){
    int val = j->data;
    cerr<<val<<" = j\n";
    if (++cnt > 11) break;
    if (seen[val]){
      j=j->next;
      cerr<<val<<" was seen\n";
      if (j == nullptr){
        i->next = nullptr;
        return listHead;
      }
      continue;
    }
    seen[val] = 1;    
    //relink .... often unnecessary
    assert(j);
    i->next = j; 
    if (j->next == nullptr){
      return listHead;
    }
    i = j;
    j = i->next;
  }
  cerr<<"endless loop\n";
}
Node* solutionSimple(Node* listHead){ //showcase 
  int seen[1001]={0}; //list payloads always between 0 and 1000
  seen[listHead->data]=1;
  for(auto n=listHead; n->next;){
    if (seen[n->next->data]){
      n->next = n->next->next;
    }else{
      n = n->next;
      seen[n->data]=1;
    }
  }
  return listHead;
}
Node* solution2(Node* listHead){ //showcase 
  int seen[1001]={0}; //list payloads always between 0 and 1000
  for(Node* n=make_shared<Node>(0, listHead).get(); n->next;){
    if (seen[n->next->data]){
      n->next = n->next->next;
    }else{
      n = n->next;
      seen[n->data]=1;
    }
  }
  return listHead;
}
Node* removeNodes(Node* listHead, int hi, int lo=0){ 
  for (auto h=listHead; h; h=h->next){
    if (lo <= h->data   &&   h->data <=hi) h->data = 11;
  }
  cout<<"After tweaking... \n ";
  dump(listHead);
  return solution2(listHead );
}
int main(int argc, char *argv[]){
  if (argc < 2){
    cout<<"Please specify a single test case by a single char\n";
    return 0;
  }
  switch(argv[1][0]){
   case '0': 
      assert(dump(removeNodes(head, 5))>0);
      break;
   case '1':
      assert(dump(removeNodes(head, 555))==1);
      break;
   case 'p': //partial
      assert(dump(removeNodes(head, 55))==5);
      break;
   default:
      cout<<"unknown test case\n";
  }
}/*Req: write a function to remove all nodes whose data > x. Return the head of the modified list.
*/
