// g++ -c this.file
//showcase: c++11 type alias, same as typedef
//showcase: c++11 enum class
//showcase: deleting while iterating a set
#include <cassert>
#include <time.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <map>
#include <memory> //shared_ptr
using namespace std;
enum class Brand {BMW, Honda};

class car{ //
  string const plate; //license
  Brand const brand;
public:
  size_t capacity; //can be increased by subclass
  car(size_t c, string const & p, Brand const & b): capacity(c), plate(p), brand(b){
    assert (this->plate.size() > 0 && "plate must be non-empty");
  }
  size_t getCapacity(){ return this->capacity; }
};
//using Fleet = vector<car const*>; //same as typedef
class SUV: public car{
  bool isRow3added;
public:
  SUV(          string const & p, Brand const & b, bool r3): car{5, p, b}, isRow3added(r3){
    this->capacity += isRow3added? 3:0;
  }
};
class Sedan: public car{
  bool isSportPackageAdded;
public:
  Sedan(        string const & p, Brand const & b, bool sp): car(5, p, b), isSportPackageAdded(sp){}
};
class CarRental {
  map<string, shared_ptr<car> > inventory; //plate -> car
  size_t available;
public:
  CarRental(): available(0) {}
  size_t getCount(){return this->available; }
  shared_ptr<car> getByPlate(string const & plate){
    if (inventory.find(plate) == inventory.end()){
      return nullptr;
    }else{
      return inventory[plate];
    }
  }
  void endRental(car const * aCar){/*to be implemented*/}
  void startRental(car const * aCar){/*to be implemented*/}
};

int main(){
  cout<<"done\n";
}
//Requirement 
