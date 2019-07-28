/* showcase placement-new
   showcase array-new
showcase std::byte representing nothing but raw memory, without a misleading notion of a char or numeric type. 

Actually, std::byte is designed as a 'backdoor' to access the underlying memory of some other object, like my Node array.
*/
#include <iostream>
#include <vector>
#include <cstddef> //std::byte, from c++17
using namespace std;
struct Node{
       double data;
       Node * next;
       Node(double _payload=0, Node * _next = nullptr)
       :next(_next), data(_payload){}
};
Node nodeArr[99];
Node * arrNew;
byte byteArr[99*sizeof(Node)];

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
    if( i > 9) return node;
  }
}
Node * fromArrayNew(){
  Node * arrNew = new Node[99];
  for (int i=0; ; ++i){
    Node * node = arrNew+i;
    node->data = 30-(i^(i<<1)) + i/100.0;
    if (i > 0) node->next = node-1;
    if( i > 9) return node;
  }
}
Node * fromPlacementNew(){
  //Node * byteArr = nodeArr; //backing array can be a static array !
  for (int i=0; ; ++i){
    Node * node = new (byteArr+i*sizeof(Node)) Node(50-(i^(i<<2)) + i/100.0);
    if (i > 0) node->next = node-1;
    //cout<< node <<" <- created a node using placement-new\n";
    if( i > 9) return node;
  }
}
int main(){
     Node const* head = fromStaticArray();
     dump(head);
     cout<<"<-- fromStaticArray; fromArrayNew -->\n";
     head = fromArrayNew();
     dump(head);
     cout<<sizeof(Node)<<" = Node size... fromPlacementNew -->\n";
     head = fromPlacementNew();
     dump(head);
}/*Can you pre-allocate storage as a node array then create a linked list?
Yes the placement-new version is best as it uses the correct ctor.
*/
