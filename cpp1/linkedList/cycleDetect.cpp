#include <iostream>
#include <cassert>
using namespace std;
#define ss if(1>0) cout
struct Node{
  float val; Node * next;
  Node (float payload, Node* n=NULL): val(payload), next(n){}
} _10(91), 
  _9(90, &_10),
  _8(80, &_9),
  _7(70, &_8),
  _6(60, &_7),
  _5(50, &_6),
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
size_t hasLoopBrent(size_t const N=2){
  assert(N>1);
  int powOfN = 1, loopLenGuess = 1 /*in case root points to itself*/;
  Node* tortoise = head;
  for (Node* hare = head->next; tortoise != hare; /*loop exit implies Loop or End*/ hare = hare->next){
    if (hare == NULL) return 0;
    cout<<hare->val<<" was checked against tortoise ("<<tortoise->val<<"); loopLenGuess = "<<loopLenGuess<<endl; 
    if (loopLenGuess == powOfN){ //Tricky! We should try to prove -- 
		//if powOfN > loopLen and powOfN > mu then we must have found the loop already
      cout<<powOfN<<" = powOfN = loopLenGuess detected.. Somehow "<<hare->val<<" must be in-loop-if-any, otherwise all nodes before "<<hare->val<<" are now discarded as definitely-outside-loop\n";
      tortoise = hare;
      powOfN *= N;
      loopLenGuess = 0;
      cout<<"   "<<tortoise->val<<" set as (payload of) new tortoise ptr, with powOfN set to "<<powOfN<<endl;
      }
    loopLenGuess++;
    }
    assert(loopLenGuess>0);
    return loopLenGuess;
}
int main(){
	_6.next = &_6; //creating a loop
	//dump();
	cout<<hasLoopBrent(5)<<" <--- is the detected loop size (0 meaning no loop)";
}