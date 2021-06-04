/*
*/
#include <stdio.h>
#include <cassert>
struct Trade{ // 
    int id;
};
size_t const SZ=2;
Trade * pool[SZ]={};
int lastSlotUsed=-1; //for assert
Trade * getInstance(){
  for (size_t i=0; i<SZ; ++i){
    if (pool[i] == nullptr) continue;
    Trade * inst = pool[i];
    pool[i] = nullptr;
    lastSlotUsed = i;
    printf("return recycled shell %p\n", inst);
    return inst;
  }
  lastSlotUsed = -1;
  Trade * ret = (Trade*) malloc(sizeof(Trade));
  printf("pool depleted :( ... return malloc() .. %p\n", ret);
  return ret;
}
/* returns the address of a recycled shell, or nullptr if deallocated

Note this function won't care if you return the same ptr twice.
*/
Trade * returnInstance(Trade * inst){
  assert (inst != nullptr) ;
  for (size_t i=0; i<SZ; ++i){
    if (pool[i] != nullptr) continue;
    pool[i] = inst;
    lastSlotUsed = i;
    printf("returned to pool at pos %d\n", i);
    return inst;
  }
  lastSlotUsed = -1;
  printf("pool full :( ... using free()\n");
  free(inst);
  return nullptr;
}
int main(){
  assert(pool[SZ-1] == nullptr);
  Trade * const t1 = getInstance();
  Trade * const t2 = getInstance();
  Trade * const t3 = getInstance();
  assert (lastSlotUsed == -1);
  
  assert(returnInstance(t1) != nullptr);
  assert (lastSlotUsed == 0);
  assert(returnInstance(t2) != nullptr);
  assert (lastSlotUsed == 1);
  
  assert(returnInstance(t3) == nullptr); // pool full
  assert(lastSlotUsed == -1);
  
  assert(getInstance() == t1);
  assert(lastSlotUsed == 0);
}/*Req: https://btv-gz.dreamhosters.com/wp-admin/post.php?post=41152&action=edit
Use C not c++
*/