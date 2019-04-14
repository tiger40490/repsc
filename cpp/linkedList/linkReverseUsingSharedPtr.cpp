/* reverse a (home-made) linked list without recursion
* uses shared_ptr to invoke delete and dtor
* convert int to c-string
* lots of const troubles :)

g++ this.file.cpp # no other args needed 
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <memory>
using namespace std;
struct Node{
       Node const * next;

       Node(Node const* _next, int _payload)
       :next(_next), payload(_payload){}
 
       ~Node(){ cout<<this->payload<<" dtor!"<<endl; }

       char * tostr() const{
          sprintf(this->buf, "%d->", payload);
          if (this->next == NULL) strcat(buf, "END");
          return buf; 
       }
private:
       int payload;
       mutable 
           char buf[99]; //big enough for me
};

//adjusts the pointers in-place. No allocation // return the new head
Node const* reverse(Node * originalHead){
  for(Node *it=originalHead,
           *lastSeen=NULL;;){
    Node const* oldNext=it->next;     
    it->next=lastSeen;
    if (NULL==oldNext) return it;
    lastSeen=it;
    it=const_cast<Node*>(oldNext);
  }
}
void dump(Node const* head){
     for (Node const* it = head; it; it = it->next){
        cout<<"" <<it->tostr()<<"";
     }
     cout<<endl;
}     

vector<shared_ptr<Node> > vec;
/* populates a linked list returnning its head node. 
also populates a global vector to ease memory mgmt.
*/
Node const* populate2(){
     Node * 
      tmp=new Node(NULL,0);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,1);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,3);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,4);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,5);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,6);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,7);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,8);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,9);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,10);vec.push_back(shared_ptr<Node>(tmp));
     tmp=new Node(tmp,99);vec.push_back(shared_ptr<Node>(tmp));
     return tmp;
}
int main(){
     Node const* oldhead = populate2();

     dump(oldhead);

     dump( //new head 
      reverse(const_cast<Node*>(oldhead)));

     vec.clear();//triggers deletes via the shared_ptr
     cin.get();
}

