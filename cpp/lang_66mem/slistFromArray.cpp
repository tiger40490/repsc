/* 
*/
#include <iostream>
#include <vector>
using namespace std;
struct Node{
       double data;
       Node * next;
       Node(double _payload=0, Node * _next = nullptr)
       :next(_next), data(_payload){}
};
Node nodeArr[99];
Node * heapArr;

void dump(Node const* head){
     for (Node const* it = head; it; it = it->next){
        cout<<"" <<it->data<<(it->next? " > ":"");
     }
     cout<<endl;
}
Node * fromStaticArray(){
  for (int i=0; ; ++i){
    Node * node = nodeArr+i;
    node->data = 110-(i^(i<<3)) + i/100.0;
    if (i > 0) node->next = node-1;
    if( i > 11) return node;
  }
}
Node * fromArrayNew(){
  Node * heapArr = new Node[99];
  for (int i=0; ; ++i){
    Node * node = heapArr+i;
    node->data = 30-(i^(i<<1)) + i/100.0;
    if (i > 0) node->next = node-1;
    if( i > 11) return node;
  }
}
int main(){
     Node const* head = fromStaticArray();
     dump(head);
     cout<<"<-- fromStaticArray; fromArrayNew -->\n";
     head = fromArrayNew();
     dump(head);
}/*Can you pre-allocate storage as a node array then create a linked list?
*/
