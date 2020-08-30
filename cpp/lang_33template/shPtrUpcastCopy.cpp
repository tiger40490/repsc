//todo: why the makeRval() output gets converted to a raw ptr? check blog

//showcase: additional dummy type U to support conversion ctor from smartPtr<U> -- the answer for the SCB-FM architect
//showcase: inside a template, print the static type of the type-argument
//showcase: new T
//showcase: type() function
#include <iostream>
#include <memory>
using namespace std;

struct B{
  virtual char type() const {return 'B' ;}
};
struct D : public B{ //private inheritance won't work
  char type() const override {return 'D' ;}
};

template<typename T> struct smartPtr{
  static smartPtr<T> makeRval(){
    cout<<"makeRval().. ";
    return smartPtr<T>(new T);
  }
  smartPtr(smartPtr<T> && arg) : raw(arg.raw){
    cout<<"move ctor\n"; //not selected by compiler
  }
  template <class U>
  smartPtr(smartPtr<U> const & arg) : raw(arg.raw){
    static_assert(is_base_of<T,U>::value); //this cvctor should work only if arg type U is convertible to (perhaps a subtype of) host type T
    T* dummy = new T;
    cout<<"conversion ctor from smartPtr of "<<arg.raw->type()<<" into smartPtr of "<<dummy->type()<<endl;
  }
  template <class U>
  smartPtr(smartPtr<U> && arg) : raw(arg.raw){
    T* dummy = new T;
    cout<<"conversion ctor from _rvr_ smartPtr of "<<arg.raw->type()<<" into smartPtr of "<<dummy->type()<<endl;
  }
  smartPtr(T* arg) : raw(arg){
    T* dummy = new T;
    cout<<"conversion ctor from RAW ptr of type "<<arg->type()<<" into smartPtr of "<<dummy->type()<<endl;
  }
  operator T*(){
    T* dummy = new T;
    cout<<"conversion OPerator to RAW ptr of type "<<dummy->type()<<endl; //not really used when the 2nd copy ctor is present
    return raw;
  }
  T* raw;
};

void takingRefStd(shared_ptr<B> & arg){ cout<<"12341 shared_ptr\n"; }
void takingNonRefStd(shared_ptr<B> arg){ cout<<"takingNonRefStd shared_ptr\n"; }
void takingRef(smartPtr<B> & arg){ cout<<"takingRef\n"; }
void takingRef_rvr(smartPtr<B> && arg){ cout<<"takingRef_rvr\n"; }
void takingNonRef(smartPtr<B> arg){ cout<<"takingNonRef\n"; }
int main(){
  shared_ptr<D> stdDD(new D); //EXPLICIT cvctor
  //shared_ptr<B> stdBB(stdDD);
  
  smartPtr<D> d2(new D);
  cout<<"\n---now constructing non-std smartPtr<B> from smartPtr<D>..\n";
  smartPtr<B> b2(d2);
  cout<<"\n---now constructing non-std smartPtr<B> from tmp smartPtr<D>..\n";
  smartPtr<B> b3 = smartPtr<D>::makeRval();
  //smartPtr<B> b3(smartPtr<int>(new int(55))); //won't compile
  cout<<"\n---now testing implicit conversions..\n";
  //return 0;
  takingNonRefStd(stdDD); //working
  takingNonRef(d2);  //working
  takingRef_rvr(d2); //working -- by creating a rval temp
  takingRef_rvr(new D); //working -- by creating a rval temp 
  //takingRef(d2); //won't compile -- takingRef() takes non-cosnt lvr but d2 converts to a rvr
  //takingRefStd(stdDD); //won't compile -- a shared_ptr<D> generates a temp sp<B> which is rval object
}
/* SCB-FM IV question: how is shared_ptr<Der> instance assignable to a shared_ptr<Base> variable when the two types are unrelated
*/
