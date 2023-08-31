/*
showcase move() passed to ctor to invite mv-ctor (if available)
showcase calling dtor directly for objects created via placement-new
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
constexpr size_t INITIAL_CAPACITY = 1;
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
    cerr<<bytes<<" bytes allocated via malloc: "<<rawPtr<<endl;
    
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
  Vec (AllocMode const m=AllocMode::PN){
    this->mode=m;
    this->sz=0;
    this->cap=INITIAL_CAPACITY;
    this->arr = new T[cap]; // use AllocMode::DC for this allocation
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

      if      (this->mode==AllocMode::DC || this->cap == INITIAL_CAPACITY){
        cerr<<"deleting old array\n";
        delete[] oldArray;
      }
      else if (this->mode==AllocMode::PN){
        cerr<<"destroying objects in old array\n";
        for (size_t i=0; i< this->cap; ++i){
          T* tgt = oldArray+i;
          tgt->~T(); 
        }
        cerr<<"   freeing old array\n"; // no problem with int
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
struct MyType{
  MyType(){cout<<"MyType no-arg called\n"; }
  MyType(int i): payload(i) {}//cout<<i<<" passed into MyType(int)\n";}
  MyType(MyType const & rhs): payload(rhs.payload) {cout<<"MyType copier called for payload = "<<payload<<endl; }
  ~MyType(){cout<<"~MyType() called for payload = "<<payload<<endl; }
  MyType & operator=(MyType const & rhs){
    this->payload = rhs.payload;
    cout<<"op=() called with payload = "<<payload<<endl;
    return *this;
  }  
  friend ostream & operator<<(ostream & os, MyType const & p){
    os<<p.payload;
    return os;
  }
private: int payload;
};
void testStruct(){
  cout<<"    v  v  v   testing with vector<MyType>....  v  v  v\n";
  for (int m=0; m<2; ++m){
    Vec<MyType> vi{static_cast<AllocMode>(m)};
    for (int i =0; i<5; ++i) vi.push_back(i+10); 
  }
}
int main(){
  testInts();
  testStrings();
  testStruct();
}
