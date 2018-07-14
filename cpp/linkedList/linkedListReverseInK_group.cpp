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
* head = &_10;
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

short const K = 5; //reverse every group of K nodes.

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
//////////// Above is tail recursion; below is iterative
size_t size(){
  size_t ret=0;
  for (Node * i=head; ; ++ret, i = i->next){
    if (i == NULL) return ret;
  }
}
void iterative(){
  size_t sz = size(); assert(sz%K == 0); //for now, i don't support stub group
  
  Node * a=head;
  Node * b=a->next;
  Node * c=b->next;
  Node * prevGroupTail = a;
  Node * xGroupTail = a;

  static size_t cnt=1;
  bool isG1 = true;

  for (;;){
    b->next = a; cout<<++cnt<<": fixing "<<*b<<" \n";
    if (cnt % K ==0){
      cout<<"end of a group\n";

      if (isG1){
        head = b;
        isG1 = false;
      }else{
        prevGroupTail->next = b; 
        prevGroupTail = xGroupTail;
        cout<<(char)prevGroupTail->data<<" === prevGroupTail\n";
        //save tail of current group needs to point it at head of new group
      }
      if (c == NULL){
          xGroupTail->next = NULL;
          return;
      }
      xGroupTail = c;
      cout<<(char)xGroupTail->data<<" = xGroupTail\n";
    }
    assert(c != NULL);
    a=b; b=c; c = c->next; //shift down the 3 markers
    // now between a and b there's no link; a is fixed; b is intact
  }
}
int main(int argc, char *argv[]) {
   tailRecursion();
   dump("---Tail recursion Reverse Completed:");
   iterative();
   dump("---Iterative Reverse Completed:");
}/*Req: https://bintanvictor.wordpress.com/2018/07/14/reverse-link-list-in-k-groups/
I won't bother to pass all leetcode tests. Real interview will focus on the key points, not those corner cases
*/