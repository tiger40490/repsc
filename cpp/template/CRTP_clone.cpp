//showcase unique_ptr returned from clone()
//showcase override keyword
#include <iostream>
#include <memory>
using namespace std;

struct AcctInterface {
  virtual unique_ptr<AcctInterface> clone() const = 0;
};

template <class Sub>
struct CloneableAccount : public AcctInterface {
  unique_ptr<AcctInterface> clone() const override {
    cout<<"CloneableAccount::clone()\n";
    Sub* ret = new Sub(static_cast<Sub const&>(*this));

    //some common procedures can be implemented here, applicable across all CloneableAccount types
    
    return unique_ptr<AcctInterface>(ret); 
    //return ret; //doesn't compile since uniqe_ptr probably has an explicit cvctor
  }
};
struct Deposit: public CloneableAccount<Deposit>{
  // no clone() override needed
  Deposit(){}
  ~Deposit(){cout<<"~Deposit dtor\n";}
  Deposit(Deposit const &){ cout<<"Deposit copy ctor\n"; }
};

int main(){
  Deposit d;
  unique_ptr<AcctInterface > clone = d.clone();
  cout<<"after calling clone()\n";
}/* demo of CRTP to implement a virtual clone(). 

Note the subclass inherites a functional virtual clone() method without doing anything. I think without TMP, base class clone() can't return a subclass instance.
*/
