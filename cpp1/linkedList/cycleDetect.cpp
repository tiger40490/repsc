#include <iostream>
#include <cassert>
using namespace std;
#define ss if(1>0) cout
struct Node{
  float val; Node * next;
  Node (float payload, Node* n=NULL): val(payload), next(n){}
} _5(50), 
  _4(40, &_5),
  _3(30, &_4),
  _2(20, &_3),
  _1(10, &_2);
Node * head = &_1;
string formatPtr(void* p){
  static size_t const targetLen=3;
  char buf[16]; //ss<<buf<<" is the rubbish before memset\n";
  size_t written = sprintf(buf, "%p\0", p);
  //ss<<buf<<" ";
  return string(buf).substr( written - targetLen );
}
void dump(string const& headline="", size_t cnt=11){ 
   cout<<headline<<endl<<"New head: ";
   for (Node* t=head; t && cnt; t=t->next, --cnt)
      cout<<t->val<<"  # "<<formatPtr(t)<<" -> "<<formatPtr(t->next)<<endl;
}
// Above is a useful, simple set-up of linked list for coding interview

/*See https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm
Can determine loop size :)*/
size_t hasLoopBrent(){
	int powOf2 = 1, loopLenGuess = 1 /*in case root points to itself*/;
	Node* tortoise = head;
  for (Node* hare = head->next; tortoise != hare; /*loop exit implies Loop or End*/ hare = hare->next){
    if (hare == NULL) return 0;
		cout<<hare->val<<" was checked against tortoise ("<<tortoise->val<<"); loopLenGuess = "<<loopLenGuess<<endl; 
    if (loopLenGuess == powOf2){ //Tricky! We should try to prove -- 
		//if powOf2 > loopLen and powOf2 > mu then we must have found the loop already
      cout<<powOf2<<" = powOf2 = loopLenGuess detected.. Somehow all nodes before "<<hare->val<<" are now discarded as definitely-outside-loop\n";
      tortoise = hare;
      powOf2 *= 2;
      loopLenGuess = 0;
			cout<<"   "<<tortoise->val<<" set as (payload of) new tortoise ptr, with powOf2 set to "<<powOf2<<endl;
		}
    loopLenGuess++;
	}
	assert(loopLenGuess>0);
	return loopLenGuess;
}
int main(){
	_5.next = &_1; //creating a loop
	//dump();
	cout<<hasLoopBrent()<<" <--- is the detected loop size (0 meaning no loop)";
}

bool hasLoopBrent2(){
  Node* currentNode = head;
  Node* tortoise = NULL;
  int countAftReset = 0;
  int scale = 2;
  cout<<"tortoise ptr starts as NULL; scale = 2\n";
  do {
    cout<<currentNode->val<<" checking against tortoise; countAftReset = "<<countAftReset<<endl; 
    if (tortoise == currentNode) return true;
    countAftReset++;
    if (countAftReset >= scale){ //We assert scale is smaller than lambda or mu but how to prove?
        tortoise = currentNode; //?
        countAftReset = 0; //=1 works
        scale = 2*scale;
        cout<<currentNode->val<<" ... set as (payload of) new tortoise ptr, with scale set to "<<scale<<endl;
    }
  } while (currentNode = currentNode->next);
  return false;
}

