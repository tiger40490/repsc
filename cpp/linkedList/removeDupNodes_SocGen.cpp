/*
todo: add tests
todo: clean up
todo: relink often unnecessary

showcase switch-case + command line arg to specify a single test case. Below is a composite command to run multiple tests:
  g++ ez_removeBadNodes_Flex.cpp && ./a.exe 0 && ./a.exe p && ./a.exe a && ./a.exe 1
*/
#include <iostream>
#include <cassert>
using namespace std;
struct Node{
  size_t data; Node * next;
  Node (size_t payload, Node* n=nullptr): data(payload), next(n){}
} _10(100), 
  _9(90, &_10),
  _8(80, &_9),
  _7(70, &_8),
  _6(60, &_7),
  _5(50, &_6),
  _4(40, &_5),
  _3(30, &_4),
  _2(20, &_3),
  _1(10, &_2);
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
  auto i=listHead, j=listHead->next; //two pointers needed
  seen[i->data]=1; //code smell
  for(;;){
    int val = j->data;
    cerr<<val<<" = j\n";
    if (seen[val]){
      j=j->next;
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
}
Node* solution2(Node* listHead, int x){ //showcase dummy node to simplify head-hunting
  Node FakeHead(INT_MIN, listHead);
  Node * p=&FakeHead;
  for (Node * q=p->next; q!=nullptr; q=q->next){
    if (q->data > x)continue;
    p->next=q;
    p=q;
  }
  p->next = nullptr;
  return FakeHead.next;
}
Node* removeNodes(Node* listHead, int hi, int lo=0){ 
  for (auto h=listHead; h; h=h->next){
    if (lo <= h->data && h->data <=hi) h->data = 10;
  }  
  dump(listHead);
  return solution1(listHead );
}
int main(int argc, char *argv[]){
  if (argc < 2){
    cout<<"Please specify a single test case by a single char\n";
    return 0;
  }
  dump(head);
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
   case 'a': //all
      assert(dump(removeNodes(head, 5555))==10);
      break;
   default:
      cout<<"unknown test case\n";
  }
}/*Req: write a function to remove all nodes whose data > x. Return the head of the modified list.
*/
