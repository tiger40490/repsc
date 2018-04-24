/*
todo: check unique_ptr<T[]> syntax
todo: prevent memory leak in the face of placement-new exception
showcase placement new
showcase unique_ptr::release()
showcase unique_ptr::get()
*/
#include <iostream>
#include <memory> //unique_ptr
#include <vector>
using namespace std;

template<typename T> struct MyVec: public vector<T>{
	size_t sz, cap;
	T* arr; //rename to ar
	size_t size()    {return sz;}
	size_t capacity(){return cap;}
	void init(size_t aa){
		arr = new T[aa]; //basic impl
		arr[0]=0;
		sz=aa;
		cap=aa;
	}
	T* alloc1(size_t newcap){//tested
		unique_ptr<T[]> //need to ensure delete[] is called
		newArr(new T[newcap]); //default construct newcap instances
		std::copy(arr, arr+sz, newArr.get());
		return newArr.release();
	}
/*Above (inefficient) uses default ctor on raw memory, followed by op=()
Below (efficient) uses placement new to copy-construct.
*/
	T* alloc2(size_t newcap){//tested
		char * raw = (char*) malloc( sizeof(T)*newcap );
		for(int i=0; i<sz; ++i){
			new (raw+i*sizeof(T)) T( *(arr+i) ); //what if throws?
		}
		return (T*)raw;
	}
	void dump(string const & headline){
		//cout<<"---- "<<headline<<" -----\n";
		for (int i=0; i<sz; ++i){
			cout<<i<<":"<<*(arr+i)<<"|";
		}cout<<endl;
	}
	void push_back(T const & t){ //redefine
		size_t const sz=size();
		if (sz == capacity()){
			size_t newcap = sz*2;
			cerr<<newcap<<" <--- will allocate to this capacity\n";
			T* const tmp = this->arr;
			this->arr = alloc2(newcap);
			delete[] tmp;
			this->cap=newcap;
		}
		*(this->arr+sz) = t; //assignment
		this->sz++;
		dump("leaving push_back");
	}
};
int main(){
	MyVec<int> v;
	v.init(1);
	for (int i =1; i<9; ++i){
		//cout<<i<<" being inserted..\n";
		v.push_back(i*10);
	}
}

/*Requirement: implement vector push_back().

I feel it's not easy to test it. So I will just compile.
*/
