#include <iostream>
using namespace std;

struct Node{
  char data;
  Node * next;
  Node (char payload, Node* n=NULL): data(payload), next(n){}
};
Node _5('5');
Node _4('4', &_5);
Node _3('3', &_4);
Node _2('2', &_3);
Node _1('1', &_2); 
Node _0('0', &_1); 
Node * head = &_0;
void dump(string const& headline){ //doesn't work with cycle
   cout<<headline<<endl<<"New head: ";
   for (Node* t=head; t; t=t->next)
      cout<< static_cast<char>(t->data) <<"  # "<<t<<" -> "<<t->next<<endl;
}
// Above is a useful, simple set-up of linked list for coding interview


/*See https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm
*/
bool hasLoopBrent(){
  Node* currentNode = head;
  Node* tortoise = NULL;
  int since = 0;
  int sinceScale = 2;
  cout<<"tortoise ptr starts as NULL\n";
  do {
	cout<<currentNode->data<<" checking against tortoise ...\n"; 
    if (tortoise == currentNode) return true;
    if (since >= sinceScale){
		cout<<currentNode->data<<" ... set as (payload of) new tortoise ptr, with sinceScale set to double\n";
        tortoise = currentNode;
        since = 0;
        sinceScale = 2*sinceScale;
    }
    since++;
  } while (currentNode = currentNode->next);
  return false;
}
int main(){
	_5.next = &_0; //creating a loop
	cout<<hasLoopBrent();
}
