/*showcase switch-case + command line arg to specify a single test case. Below is a composite command to run multiple tests:
  g++ ez_removeBadNodes_Flex.cpp && ./a.exe 0 && ./a.exe p && ./a.exe a && ./a.exe 1
*/

//todo: So far we have two in-place solutions. Add a copy-filter solution, less efficient but hopefully simpler.

#include <iostream>
#include <cassert>
using namespace std;
struct Node{
  float data; Node * next;
  Node (float payload, Node* n=nullptr): data(payload), next(n){}
} _10(51), 
  _9(90, &_10),
  _8(48, &_9),
  _7(70, &_8),
  _6(60, &_7),
  _5(50, &_6),
  _4(40, &_5),
  _3(30, &_4),
  _2(120, &_3),
  _1(110, &_2);
Node * head = &_1;
size_t dump(Node *h){
  size_t ret = 0;
  for (; h; h=h->next){
    cout<<h->data<<"->";
    ++ret;
  }
  cout<<"nullptr\n";
  return ret;
}
Node* solution1(Node* listHead, int x){ //submitted to hackerrank
    while (listHead != nullptr && listHead->data > x){
        Node* a = listHead;
        listHead = listHead->next;
    } // from now on, listHead is the correct value to return
    Node* p = listHead;
    if (p == nullptr){
      return nullptr;
    }
    Node* q = p->next;   
    while (q != nullptr){
        if (q->data > x){
            q= q->next;
            if (q==nullptr) {
                p->next=nullptr;
                break;
            }
            continue;
        }
        assert(q->data <= x);
        p->next = q;
        p=q;
        q=p->next;
    }
    return listHead;
}
Node* solution2(Node* listHead, int x){ //showcase FakeHead to simplify head-hunting
  Node FakeHead(INT_MIN, listHead);
  Node * p=&FakeHead;  // invariant: p is always a Good node i.e. not to be removed
  for (Node * q=p->next; q!=nullptr; q=q->next){
    if (q->data > x)continue;
    p->next=q;
    p=q;
  }
  p->next = nullptr; // p is now the last Good node. Special case: p==FakeHead if all original nodes are bad
  return FakeHead.next;
}
Node* removeNodes(Node* listHead, int x){ //return head of modified list
  return solution2(listHead, x);
}
int main(int argc, char *argv[]){
  if (argc < 2){
    cout<<"Please specify a single test case by a single char\n";
    return 0;
  }
  switch(argv[1][0]){
   case '0': 
      assert(dump(removeNodes(head, 15))==0);
      break;
   case '1':
      assert(dump(removeNodes(head, 35))==1);
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
