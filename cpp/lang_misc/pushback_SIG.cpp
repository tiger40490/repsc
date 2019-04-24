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
template<typename T> struct MyVec{
	size_t sz, cap; //2 fields needed
	AllocMode mode;
	T* arr;
	size_t size()    {return sz;}
	size_t capacity(){return cap;}
	void uninit (AllocMode const m){ //leave raw memory uninitialized
		this->mode=m;
		size_t const cnt1=1;
		arr = new T[cnt1];
		cap=cnt1;
		sz=0;
	}
	T* alloc1(size_t const newcap){
		assert(this->mode == AllocMode::DC); //DC = DefaultConstruct
		unique_ptr<T[]> newArr //need to ensure delete[] is called
		  = make_unique<T[]>(newcap); //default-construct this many instances of T
		std::copy(arr, arr+sz, newArr.get()); //copy from original arr to new array
		cout<<"Returning from alloc11111\n";
		return newArr.release();
	}
/*Above (inefficient) uses default ctor on raw memory, followed by op=()
Below (efficient) uses placement new to copy-construct.
*/
	T* alloc2(size_t const newcap){//tested
		assert(this->mode == AllocMode::PN);	//PlacementNew
		
		/*cast to char ptr, to support raw+1
		but why reinterpret_cast not needed?
		*/
		unique_ptr<char> raw(
			static_cast<char*>(   malloc(sizeof(T)*newcap)   )
		);
		for(int i=0; i<sz; ++i){
			new (raw.get()+i*sizeof(T)) T( *(arr+i) ); //what if throws? unique_ptr should free all memory
		}
		cout<<"Returning from alloc22222\n";
		return (T*)raw.release();
	}
	void dump(string const & headline){
		//cout<<"---- "<<headline<<" -----\n";
		for (int i=0; i<sz; ++i){
			cout<<i<<":"<<*(arr+i)<<"|";
		}cout<<endl;
	}
	void push_back(T const & t){
		size_t const sz=size();
		if (sz == capacity() || sz==0){
			size_t newcap = sz==0? 1:sz*2;
			cerr<<newcap<<" <--- will allocate to this capacity\n";
			T* const tmp = this->arr;
			if      (this->mode==AllocMode::DC)
  			  this->arr = alloc1(newcap);
			else if (this->mode==AllocMode::PN)
  			  this->arr = alloc2(newcap);
		  
			delete[] tmp;
			this->cap=newcap;
		}
		*(this->arr+sz) = t; //assignment without calling the ctor?? I think PN mode needs another PN
		this->sz++;
		dump("leaving push_back");
	}
};
int main(){
	MyVec<int> v;
	for (int m=0; m<2; ++m){
		v.uninit(static_cast<AllocMode>(m));
		for (int i =0; i<5/*9 is good*/; ++i) v.push_back(i+10);
	}
}
/*Requirement: implement vector push_back().
*/
