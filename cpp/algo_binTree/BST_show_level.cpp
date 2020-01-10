#include "binTreeUtil.h"
#include <iostream>
#include <queue>
using namespace std;

struct TNode {
    int data;
    TNode *left, *right, *next;
    TNode(int x, TNode * le = NULL, TNode * ri = NULL) : data(x), left(le), right(ri), next(NULL) {}
};
    TNode _15(15);
    TNode _14(14);
    TNode _13(13);
    TNode _12(12);
    TNode _11(11);
    TNode _10(10);
    TNode _9(9);
    TNode _8(8);
    TNode _7(7, &_14, &_15);
    TNode _6(6, NULL, &_13);
    TNode _5(5, &_10, NULL);
    TNode _4(4, NULL, &_9);
    TNode _3(3, &_6,  &_7);
    TNode _2(2, &_4,  &_5);
    TNode root(1, &_2, &_3);
    TNode marker(-1); //to be added to queue to mark new level

TNode * dequeue(queue<TNode*> & q){
    assert(!q.empty());
    TNode * n = q.front();
    q.pop();
    return n;
}
void BFT(){
  queue<TNode *> q;
  size_t height=0;

  for( q.push(&marker), q.push(&root); !q.empty();){
    TNode * n = dequeue(q);
    if (n == &marker){
        if (q.empty()){
                cout<<"  ^^^^^^^^^^"<<endl;
                break;
        }
        n = dequeue(q);
        q.push(&marker); //move the marker to end of queue
        cout<<"starting height # "<<++height<<endl; 
    } 
    int dataL = 0, dataR=0; 
    if (n->left){
        cout<<"pushing "<<n->left->data<<endl; q.push(n->left);
        dataL = n->left->data;
    }
    if (n->right){
        cout<<"pushing "<<n->right->data<<endl; 
        q.push(n->right);
        dataR = n->right->data;
    }
    cout<<dataL<<" <- "<<n->data<<" -> "<<dataR<<endl;// "  #  next is "<<dataN<<endl;
  }
}
int main() {
    BFT();
}
