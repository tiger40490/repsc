/*
showcase move() passed to ctor to invite mv-ctor (if available)
showcase copy-construct on heap but not allocating -- by placement-new!
showcase make_unique<T[]> array-form
showcase casting uninitialized heap ptr to char-ptr
showcase unique_ptr::release()
showcase unique_ptr::get()
showcase casting from int to enum
showcase scoped enum
*/
#include <iostream>
#include <memory> //unique_ptr
#include <assert.h>
using namespace std;

enum class AllocMode{PN, DC};
template<typename T> class Vec{
  size_t sz, cap; //2 fields needed
  AllocMode mode;
  T* arr; // underlying array
  T* allocDefaultConstruct(size_t const newcap){
    assert(this->mode == AllocMode::DC); //DC = DefaultConstruct
    unique_ptr<T[]> newArr //need to ensure delete[] is called
      = make_unique<T[]>(newcap); //Step 1: default-construct this many instances of T
    
    std::copy(arr, arr+sz, newArr.get()); //Step 2: one-by-one assign from original arr to new array
    cout<<"Returning from alloc_DC\n";
    return newArr.release();
  }
/*Above (inefficient) uses default ctor on raw memory, followed by copy-assignment. For simple types of int, this inefficiency is tolerable.

Below (efficient) uses placement new followed by copy-construct.
*/
  T* allocPlacementNew(size_t const newcap){//tested
    assert(this->mode == AllocMode::PN);  //PlacementNew
    
    // Step 1: allocate raw memory.
    //    cast to char ptr, to support raw+1 but why reinterpret_cast not needed?

    size_t bytes{ sizeof(T)*newcap };
    //cerr<<bytes<<" bytes to be allocated via malloc\n";
    void * rawPtr{ malloc(bytes) };
    if (rawPtr == nullptr){
      cerr<<"malloc failed\n";
      return nullptr;
    }
    //cerr<<bytes<<" bytes allocated via malloc: "<<rawPtr<<endl;
    
    unique_ptr<char> raw(
      static_cast<char*>(rawPtr)
    );
    //cerr<<newcap<<" slots saved in uniq ptr\n";
    for(int i=0; i<sz; ++i){ //Step 2: in-place copy-construct
      //T &  lvr = *(arr+i);
      T && rvr = move(*(arr+i));
      new (raw.get()+i*sizeof(T)) T( rvr ); //what if throws? unique_ptr should free all memory
    }
    cerr<<"Returning from alloc_PN\n";
    return (T*)raw.release();
  }
  void dump(string const & headline){
    //cout<<"---- "<<headline<<" -----\n";
    for (int i=0; i<sz; ++i){
      cout<<i<<":"<<*(arr+i)<<"|";
    }cout<<endl;
  }
public:
  size_t size()    const {return sz;}
  size_t capacity()const {return cap;}
  Vec (AllocMode const m=AllocMode::PN){ //leave raw memory uninitialized
    this->mode=m;
    this->sz=0;
    this->cap=1;
    this->arr = new T[cap];
  }
  void push_back(T const & incoming){
    size_t const sz=size();
    if (sz == capacity()){
      size_t newcap = capacity()*2;
      cerr<<newcap<<" <--- will allocate to this capacity\n";
      T* const oldArray = this->arr;
      if      (this->mode==AllocMode::DC)
          this->arr = allocDefaultConstruct(newcap);
      else if (this->mode==AllocMode::PN)
          this->arr = allocPlacementNew(newcap);

      cerr<<"deleting old array\n";
      if      (this->mode==AllocMode::DC){
        delete[] oldArray; // seg fault for PlacementNew + vector<string>
      }
      else if (this->mode==AllocMode::PN && 1==0){
        // need to call dtor on each object then 
        free(oldArray);
      }

      this->cap=newcap;
    }
    //cerr<<"copying the incoming element\n";
    new (this->arr+sz) T( incoming ); // Using placement-new for both DC and PN mode
    //cerr<<"incrementing this->sz\n";
    this->sz++;
    dump("leaving push_back");
  }};
void testInts(){
  for (int m=0; m<2; ++m){
    Vec<int> vi{static_cast<AllocMode>(m)};
    for (int i =0; i<5; ++i) vi.push_back(i+10); // int is error-free
  }
}
void testStrings(){
  cout<<"    v  v  v   testing with vector<string>.... likely to fail  v  v  v\n";
  for (int m=0; m<2; ++m){
    Vec<string> vs{static_cast<AllocMode>(m)};
    for (int i =0; i<5; ++i) vs.push_back(to_string(i+10));
  }
}
int main(){
  testInts();
  testStrings();
}
