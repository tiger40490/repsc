//todo: 
#include <iostream>
#include <assert.h>
using namespace std;

struct B1empty{};
struct B2empty{};
struct B1nonEmpty{
  char f1[3]; //without this field, all 3 object addresses are identical
};
struct B2nonEmpty{
  char f2[6]; //without this field, all 3 object addresses are identical
};
template<typename B1, typename B2, char mode>
struct D: public B1, B2{
  test(){
    auto pb1 = dynamic_cast<B1*>(this);
    auto pb2 = dynamic_cast<B2*>(this);
    cout<<(int)mode<<" <===== new mode in a new test\n";
    cout<<this<<" = addr of derived object \n";
    cout<<pb1<<" = addr after casting to B1* \n"; //same as der
    cout<<pb2<<" = addr after casting to B2* \n"; //different from der
    assert((void*)pb1==(void*)this);

    cout<<"*this size = "<<sizeof(*this)<<endl;
    cout<<"D  size = "<<sizeof(D)<<endl;    
    cout<<"B1 size = "<<sizeof(B1)<<endl;
    cout<<"B2 size = "<<sizeof(B2)<<endl;
    
    if       (mode == 2){
      assert((void*)pb2!=(void*)this);
    }else if (mode <=1){
      assert(sizeof(B1)==1 || 1==sizeof(B2));
      assert((void*)pb2==(void*)this);
      if (mode == 0){
        assert(sizeof(B1)==1 && 1==sizeof(B2));
      }
    }else{ 
      assert(1==0);
    }
  }//method
};
int main(){
  D<B1nonEmpty, B2nonEmpty, 2>().test();
  D<B1empty, B2nonEmpty, 1>().test();
  D<B1nonEmpty, B2empty, 1>().test();
  D<B1empty, B2empty, 0>().test();
}/* Q: dynamic_cast always(?) gives the same address?
   A: not always. Consider MI.
   A: if any one of the two base classes is a pure-interface (i.e. no instance field) then YES
   
Empty base-class optimiztion

This optmization only zeros out the runtime size of baseclass subobject. All other sizes of empty types are one.
   
Suppose Der subclasses B1 and B2.
If B1 (or B2) is empty, then sizeof(B1) == 1 not zero, but at run time, the Der object size shows the B1 object has zero size.

If all of Der, B1 and B2 are empty, we know sizeof(Der) == 1, but how about sizeof(an_Der_instance)? Also 1
*/