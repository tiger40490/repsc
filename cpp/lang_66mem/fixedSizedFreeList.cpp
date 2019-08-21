/*
todo: add more tests
showcase placement-new

Realistic app Should check the MAX before placement-new

Note: placement-new should be minimized inside the free list 
*/
#include <iostream>
#include <cassert>
using namespace std;
size_t const PTR_SZ=sizeof(void*);
template <size_t CHUNK=3, size_t MAX=100> struct FreeList{
  struct Node{
    Node * next=nullptr;
    uint8_t payload[CHUNK];
    Node(): next(nullptr), payload{1} //c++11 syntax
    { //experimenting with array initialization:
      assert(payload[0]==1); payload[0]=0;
      if (CHUNK > 0)
        assert(payload[1]==0 && "All elements except first is default-initialized to 0");
      assert(payload[CHUNK-1]==0);
    }
  } __attribute__((packed));

  FreeList(){
    auto mallocSz = MAX * (CHUNK+PTR_SZ);
    this->base = malloc(mallocSz); //should use sbrk() if available
    this->head = nullptr;
    cout<<mallocSz<<" bytes allocated at "<<base<<endl;
  }
  void ffree(void * const ptr_arg){//fairly fast
    char * const tmp = (char*) ptr_arg - PTR_SZ;
    //We will assume ptr_arg was originally from a Node
    Node * node = static_cast<Node*> ((void*)tmp);
    node->next = this->head; this->head = node;
    cout<<ptr_arg<<" passed into ffree(). New free list head = "<<node<<endl;
    assert ( this->head != ptr_arg);
    assert (!this->isNullHead());
  }
  /* 
  Returns the current head node
  Updates this->head. Possibly null, since we are lazy setting up next Node. We delay it until needed.
  Updates this->base iFF allocating from the raw array
  */
  void * fmalloc(size_t sz){
    if (sz > CHUNK){
      cout<<"fmalloc() received over-sized request\n";
      return nullptr;
    }
    if(head == nullptr){
      head  = new (base) Node(); //create new Node from raw array
      assert (head->next == nullptr && "Node() should null-initialize");
      char * tmp = (char*)this->base - sizeof(Node);
      this->base = (void*) tmp;
      cout<<this->base<<" = new BASE\n";
    }else{
      cout<<" :) Lucky to find an existing head node, probably recycled :)\n";
    }
    assert (head != nullptr);
    void * const ret = this->head->payload;   
    assert (ret != nullptr);
    head = head->next;
    cout<<head<<" = the new free list head, after returning "<<ret<<" from fmalloc()\n";
    return ret;
  }
  bool isNullHead() const {
    return this->head == nullptr;
  }
private:
  Node * head;
  void * base;
};
int main(){
  struct Trade{
    int id;
    Trade(int i): id(i){
      cout<<"   New Trade @ "<<this<<" with id = "<<id<<endl;
    }
  };
  size_t const chunk=4;
  FreeList<chunk> flist;
  void * 
  newAddr = flist.fmalloc(9999);  assert (newAddr == nullptr);
  newAddr = flist.fmalloc(sizeof(Trade));
  assert (flist.isNullHead());  
  Trade * trade2 = new (newAddr) Trade(-22);

  void * 
  newAddrX = flist.fmalloc(1);
  assert (flist.isNullHead());  

  newAddr = flist.fmalloc(4);
  assert (flist.isNullHead());
  Trade * trade4 = new (newAddr) Trade(-44);

  flist.ffree(newAddrX);
  flist.ffree(trade4);
  
  newAddr = flist.fmalloc(3);
  assert (!flist.isNullHead());
  Trade * trade3 = new (newAddr) Trade(-33);

  assert (trade2->id == -22);
  flist.ffree(trade2);

  assert (trade3->id == -33);  
}/*Req: https://bintanvictor.wordpress.com/wp-admin/post.php?post=33040&action=edit

*/