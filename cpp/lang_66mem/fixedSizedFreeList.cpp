/*
todo: add more tests
todo: check the MAX before placement-new
showcase placement-new

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
    Node(): next(nullptr), payload{0} {}
  } __attribute__((packed));

  FreeList(){
    auto mallocSz = MAX * (CHUNK+PTR_SZ);
    this->base = malloc(mallocSz); //should use sbrk() if available
    this->head = nullptr;
    cout<<mallocSz<<" bytes allocated at "<<base<<endl;
  }
  void ffree(void * const ptr){//fairly fast
    char * const tmp = (char*) ptr - PTR_SZ;
    Node * node = static_cast<Node*> ((void*)tmp);
    node->next = this->head;
    this->head = node;
    cout<<ptr<<" passed into ffree(). New free list head = "<<node<<endl;
    assert ( this->head != ptr);
    assert (!this->isNullHead());
  }
  /* 
  returns the current head node
  updates this->head, possibly null
  updates this->base iFF allocating from the raw array
  */
  void * fmalloc(size_t sz){
    assert(sz <= CHUNK);
    if(head == nullptr){
      head  = new (base) Node();
      assert (head->next == nullptr);
      char * tmp = (char*)this->base - sizeof(Node);
      this->base = (void*) tmp;
      cout<<this->base<<" = new BASE\n";
    }else{
      cout<<" :) Lucky to find a head node with a live follower :)\n";
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
      cout<<"   New Trade created@ "<<this<<" with id = "<<id<<endl;
    }
  };
  size_t const chunk=4;
  FreeList<chunk> flist;
  void * 
  newAddr = flist.fmalloc(2);
  assert (flist.isNullHead());  
  Trade * trade2 = new (newAddr) Trade(-22);

  void * 
  newAddrX = flist.fmalloc(1);
  assert (flist.isNullHead());  
  newAddr = flist.fmalloc(4);
  assert (flist.isNullHead());
  Trade * trade4 = new (newAddr) Trade(-44);
  flist.ffree(newAddrX);
  flist.ffree(newAddr);
  
  newAddr = flist.fmalloc(3);
  assert (!flist.isNullHead());
  Trade * trade3 = new (newAddr) Trade(-33);
  assert (trade2->id == -22);
}/*Req: https://bintanvictor.wordpress.com/wp-admin/post.php?post=33040&action=edit

*/