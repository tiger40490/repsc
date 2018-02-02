#include <iostream>
using namespace std;

struct Node{
  float data;
  Node * next;
  Node (float payload, Node* n=NULL): data(payload), next(n){}
};
Node _5(5);
Node _4(4, &_5);
Node _3(3, &_4);
Node _2(2, &_3);
Node _1(1, &_2); 
Node _0(0, &_1); 
Node * head = &_0;
void dump(string const& headline){ //doesn't work with cycle
   cout<<headline<<endl<<"New head: ";
   for (Node* t=head; t; t=t->next)
      cout<< static_cast<char>(t->data) <<"  # "<<t<<" -> "<<t->next<<endl;
}
// Above is a useful, simple set-up of linked list for coding interview


/*See https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm
Can determine loop size :)
*/
bool hasLoopBrent(){
	int power = 1, loopLenGuess = 1;
    Node* tortoise = head;
	Node* hare = tortoise->next;
    for (; tortoise != hare; hare = hare->next){
        if (hare == NULL) return false;
		cout<<hare->data<<" checking against tortoise; loopLenGuess = "<<loopLenGuess<<endl; 
        if (power == loopLenGuess){ //We should try to prove -- 
		//if power > loopLen and power > mu then we must have found the loop already
            tortoise = hare;
            power *= 2;
            loopLenGuess = 0;
			cout<<"   "<<tortoise->data<<" set as (payload of) new tortoise ptr, with power set to "<<power<<endl;
		}
        loopLenGuess++;
	}
	cout<<"    Loop size = "<<loopLenGuess<<endl;
	return true;
}
bool hasLoopBrent2(){
  Node* currentNode = head;
  Node* tortoise = NULL;
  int countAftReset = 0;
  int scale = 2;
  cout<<"tortoise ptr starts as NULL; scale = 2\n";
  do {
	cout<<currentNode->data<<" checking against tortoise; countAftReset = "<<countAftReset<<endl; 
    if (tortoise == currentNode) return true;
    countAftReset++;
    if (countAftReset >= scale){ //We assert scale is smaller than lambda or mu but how to prove?
        tortoise = currentNode; //?
        countAftReset = 0; //=1 works
        scale = 2*scale;
		cout<<currentNode->data<<" ... set as (payload of) new tortoise ptr, with scale set to "<<scale<<endl;
    }
  } while (currentNode = currentNode->next);
  return false;
}
int main(){
	_5.next = &_4; //creating a loop
	cout<<hasLoopBrent();
}
