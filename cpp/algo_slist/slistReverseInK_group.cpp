/*
showcase multiple variable declaration after struct declaration
showcase multiple increments within for-loop header
*/
#include <iostream>
#include <cassert>
using namespace std;
struct Node{
  int const data;
  Node * next;
  Node (int payload, Node* n=NULL): data(payload), next(n){}
  friend ostream & operator<<(ostream & os, Node const & t){
    os<<static_cast<char>(t.data) <<"  @ "<<&t<<" -> "<<t.next;
    return os;
  }
} _1('1'), //tail
_2('2', &_1),
_3('3', &_2),
_4('4', &_3),
_5('5', &_4),
_6('6', &_5),
_7('7', &_6),
_8('8', &_7),
_9('9', &_8),
_10('A', &_9),
* head = &_8;
void dump(string const& headline){
   cout<<headline<<endl<<"New head: ";
   size_t cnt=0;
   for (Node* t=head; t; t=t->next){
      cout<< *t <<endl;
      if (++cnt > 9) break;
   }
   cout<<"==================\n";
}
// Above is a useful, simple set-up of linked list for coding interview

size_t const K = 4; //reverse every group of K nodes. This program allows K to be anything but meaningful value is between 2 and list length

/** Each recursive call modifies exactly one node, b in this case
 * Pre-condition: A used to point to b but now A has already been fixed in the previous call
 * Return type is unused, but makes the exit if-block shorter
 */
void * reverse1(Node* A, Node* b){
  assert(A->next != b);
  Node * c = b->next;
  b->next = A;  //cout<<*b<<" fixed\n";
  if (c == NULL) return head = b; //exit condition
  reverse1(b,c);
}
void tailRecursion(){
        Node * b = head->next;
        head->next = NULL;
        reverse1(head, b);
}
//////////// Above is tail recursion without K-groups; below is iterative
size_t size(){
  size_t ret=0;
  for (Node * i=head; ; ++ret, i = i->next){
    if (i == NULL) return ret;
  }
}
void iterative(){
  size_t cnt=1, sz = size();
  if (K<=1 || K > sz) return;
  Node * const oldHead = head;
  Node * tailFar = oldHead;
  Node * tailNear = oldHead;
  Node * a=oldHead;
  Node * b=a->next;
  Node * c=b->next;

  for (;;a=b, b=c, c = c->next){ //3 pointers never reseated within the loop body
    b->next = a; cout<<++cnt<<": fixing "<<*b<<" \n";
    if (cnt % K ==0){
      cout<<"end of a group\n";

      if (head == oldHead){ head = b; } //special handling of first node
      tailFar->next = b; 
      tailFar = tailNear;
      //cout<<(char)tailFar->data<<" === tailFar\n";
      if (cnt == sz/K*K){ //Stub: all remaining nodes are kept as is
        tailNear->next = c;
        return;
      }
      tailNear = c; //pointer therein to be adjusted
      //cout<<(char)tailNear->data<<" = tailNear\n";
    }
    assert(c != NULL && "last node should be handled by the if-block");
  }
}
int main(int argc, char *argv[]) {
   tailRecursion();
   dump("---Tail recursion Reverse Completed:");
   iterative();
   dump("---Iterative Reverse Completed:");
}/*Req: https://bintanvictor.wordpress.com/2018/07/14/reverse-link-list-in-k-groups/
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as is.

I won't bother to pass all leetcode tests. Real interview will focus on the key points, not those corner cases
*/
