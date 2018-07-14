#include <iostream>
#include <cassert>
using namespace std;
struct Node{
  int const data;
  Node * next;
  Node (int payload, Node* n=NULL): data(payload), next(n){}
  friend ostream & operator<<(ostream & os, Node const & t){
    os<<static_cast<char>(t.data) <<"  # "<<&t<<" -> "<<t.next;
    return os;
  }
} _1('1'), //tail
_2('2', &_1),
_3('3', &_2),
_4('4', &_3),
_5('5', &_4),
_6('6', &_5),
_7('7', &_6),
* head = &_7;
void dump(string const& headline){
   cout<<headline<<endl<<"New head: ";
   for (Node* t=head; t; t=t->next)
      cout<< *t <<endl;
   cout<<"==================\n";
}
// Above is a useful, simple set-up of linked list for coding interview

/** Each recursive call modifies exactly one node, b in this case
 * Pre-condition: A used to point to b but now A has already been fixed in the previous call
 * Return type is unused, but makes the exit if-block shorter
 */
void * reverse1(Node* A, Node* b){
  assert(A->next != b);
  Node * c = b->next;
  b->next = A; cout<<*b<<" fixed\n"; //fix node b
  if (c == NULL) return head = b; //exit condition
  reverse1(b,c);
}
void tailRecursion(){
        Node * b = head->next;
        head->next = NULL;
        reverse1(head, b);
}

void iterative(){
  Node * a=head;
  Node * b=a->next;
  Node * c=b->next;
  // marker variables on 3 consecutive nodes

  a->next=NULL; // first fix the head node

  for (;;){
    b->next = a; //fix the "b" node
    a=b; b=c; c = c->next; //shift down the 3 markers
    // now between a and b there's no link; a is fixed; b is intact

    if (c == NULL){
      head = b;
      head->next = a;
      break;
    }
  }
}
int main(int argc, char *argv[]) {
   iterative();
   dump("---Iterative Reverse Completed:");
   tailRecursion();
   dump("---Tail recursion Reverse Completed:");
}/*Req: https://bintanvictor.wordpress.com/2018/07/14/reverse-link-list-in-k-groups/
I won't bother to pass all leetcode tests. Real interview will focus on the key points, not those corner cases
*/