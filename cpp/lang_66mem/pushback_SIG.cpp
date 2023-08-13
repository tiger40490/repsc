/*
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

enum class AllocMode{DC, PN};
template<typename T> class Vec{
	size_t sz, cap; //2 fields needed
	AllocMode mode;
	T* arr; // underlying array
	T* allocDefaultConstruct(size_t const newcap){
		assert(this->mode == AllocMode::DC); //DC = DefaultConstruct
		unique_ptr<T[]> newArr //need to ensure delete[] is called
		  = make_unique<T[]>(newcap); //Step 1: default-construct this many instances of T
    
		std::copy(arr, arr+sz, newArr.get()); //Step 2: one-by-one assign from original arr to new array
		cout<<"Returning from alloc11111\n";
		return newArr.release();
	}
/*Above (inefficient) uses default ctor on raw memory, followed by copy-assignment. For simple types of int, this inefficiency is tolerable.

Below (efficient) uses placement new followed by copy-construct.
*/
	T* allocPlacementNew(size_t const newcap){//tested
		assert(this->mode == AllocMode::PN);	//PlacementNew
		
		/* Step 1: allocate raw memory.
        cast to char ptr, to support raw+1 but why reinterpret_cast not needed?
		*/
		unique_ptr<char> raw(
			static_cast<char*>(   malloc(sizeof(T)*newcap)   )
		);
    
		for(int i=0; i<sz; ++i){ //Step 2: in-place copy-construct
			new (raw.get()+i*sizeof(T)) T( *(arr+i) ); //what if throws? unique_ptr should free all memory
		}
		cout<<"Returning from alloc22222\n";
		return (T*)raw.release();
	}
	void dump(string const & headline){
		//cout<<"---- "<<headline<<" -----\n";
		for (int i=0; i<sz; ++i){
			cout<<i<<":"<<*(arr+i)<<" | ";
		}cout<<endl;
	}
public:
	size_t size()    const {return sz;}
	size_t capacity()const {return cap;}
	Vec (AllocMode const m){ //leave raw memory uninitialized
		this->mode=m;
		this->sz=0;
		this->cap=1;
		this->arr = new T[cap];
	}
	void push_back(T const & t){
		size_t const sz=size();
		if (sz == capacity()){
			size_t newcap = capacity()*2;
			cerr<<newcap<<" <--- will allocate to this capacity\n";
			T* const tmp = this->arr;
			if      (this->mode==AllocMode::DC)
  			  this->arr = allocDefaultConstruct(newcap);
			else if (this->mode==AllocMode::PN)
  			  this->arr = allocPlacementNew(newcap);
		  
			delete[] tmp;
			this->cap=newcap;
		}
		*(this->arr+sz) = t; //assignment without calling the ctor?? I think PN mode needs another PN
		this->sz++;
		dump("leaving push_back");
	}};
void test(){
	for (int m=0; m<2; ++m){
		Vec<int> v{static_cast<AllocMode>(m)};
		for (int i =0; i<5; ++i) v.push_back(i+10);
	}
}
int main(){
	test();
}
/*Requirement: implement vector push_back().
*/
