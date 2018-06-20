//todo: add tests
#include <iostream>
#include <cassert>
using namespace std;
#define ss if(1>0) cout
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
Node* solution1(Node* listHead, int x) {
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
Node* solution2(Node* listHead, int x) {
  Node FakeHead(0, listHead);
  Node * p=&FakeHead;
  for (Node * q=p->next; q!=nullptr; q=q->next){
    if (q->data > x){
      //cout<<"continue after "<<q->data<<endl;
      continue;
    }
    assert(q->data <= x);
    p->next=q;
    p=q;
  }
  p->next = nullptr; //?
  return FakeHead.next;
}
Node* removeNodes(Node* listHead, int x) {
  return solution1(listHead, x);
}
int main(){ //run one of these tests, not 2 together!
  //assert(dump(removeNodes(head, 15))==0);
  //assert(dump(removeNodes(head, 35))==1);
  //assert(dump(removeNodes(head, 55))==5);
  assert(dump(removeNodes(head, 5555))==10);
}/*Req: write a function to remove all nodes whose data > x. Return the head of the modified list.
*/