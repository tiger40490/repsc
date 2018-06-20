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
  _1(10, &_2);
Node * head = &_1;

Node* removeNodes(Node* listHead, int x) {
    while (listHead != nullptr && listHead->data > x){
        Node* a = listHead;
        listHead = listHead->next;
    }        
    Node* p = listHead;
    if (p == nullptr){
      cout<<9999<<endl;
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
void dump(Node *h){
  for (; h; h=h->next){
    cout<<h->data<<"->";
  }
  cout<<"nullptr\n";
}
int main(){
  head=removeNodes(head, 55);
  dump(head);
}