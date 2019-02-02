#include <iostream>
using namespace std;

template <typename Sub> struct NumericalFunctions {
    void square(){ //a reusable code to be "inherited" by any subclass
        Sub& underlying = static_cast<Sub&>(*this);
        // cast to Sub* i.e. pointer is probably more common and I tested too.

        //Now we can Access subclass instance without using virtual function!
        underlying.setValue(underlying.getValue() * underlying.getValue());
        cout<<"from inside superclass square(), you can even access subclass field: "<<underlying._value<<endl;
    }
};
struct Sensitivity : public NumericalFunctions<Sensitivity> {
    double _value;
    double getValue() const{ return _value; }
    void setValue(double value){ _value = value; }
};
int main(){
  Sensitivity * inst = new Sensitivity;
  inst->setValue(17);
  inst->square();
  cout<<inst->getValue();
}
