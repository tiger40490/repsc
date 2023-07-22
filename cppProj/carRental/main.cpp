// g++ -c this.file
//showcase: c++11 enum class
#include <assert.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <memory> //shared_ptr
using namespace std;
enum class Brand {BMW, Honda};

class car{ //
  string const plate; //license
  Brand  const brand;
  bool isAvailable;
public:
  car(string const & p, Brand const & b): plate(p), brand(b), isAvailable(true){
    assert (this->plate.size() > 0 && "plate must be non-empty");
  }
  string const & getPlate()   const{ return this->plate; } 
  Brand          getBrand()   const{ return this->brand; }
  bool           getStatus()  const{ return this->isAvailable; }
  virtual size_t getSeatCnt() const{ return 5; }
  void markAvailable()   {this->isAvailable = true; }
  void markUnAvailable() {this->isAvailable = false; }  
};
class SUV: public car{
  bool isRow3Up;
public:
  SUV(string const & p, Brand const & b, bool r3): car(p, b), isRow3Up(r3){}
  void addRow3()   { this->isRow3Up = true;}
  void removeRow3(){ this->isRow3Up = false;}
  bool checkRow3() const{ return this->isRow3Up;}
  size_t getSeatCnt() const{
    return this->isRow3Up? 8:5;
  }
};
class Sedan: public car{
  bool isSportPackageAdded;
public:
  Sedan(string const & p, Brand const & b, bool sp): car(p, b), isSportPackageAdded(sp){}
};
class CarRental {
  unordered_map<string, shared_ptr<car> > inventory; //plate -> car
  unordered_set<shared_ptr<car> > available;
public:
  CarRental() {}
  size_t getFreeCnt(){return this->available.size(); }
  shared_ptr<car> findCarByPlate(string const & plate){
    if (inventory.find(plate) == inventory.end()){
      return nullptr;
    }else{
      return inventory[plate];
    }
  }
  size_t addCar(car & newCar){
    shared_ptr<car> ptr{&newCar};
    this->available.insert(ptr);
    string const & plate = newCar.getPlate();
    this->inventory[plate] = ptr;
    return this->getFreeCnt();
  }
  void endRental(string const & plate){
    auto car = findCarByPlate(plate);
    if (car) {
      if (car->getStatus()){
        cout<<plate<<" is already in our garage, not rented out!\n";
       }else{
        car->markAvailable();
        this->available.erase(car);
      }
    }else{
      cout<<plate<<" is not our car\n";
    }    
  }
  void startRental(string const & plate){
    auto car = findCarByPlate(plate);
    if (car) {
      if (car->getStatus()){
        car->markUnAvailable();
        this->available.insert(car);
      }else{
        cout<<plate<<" is unavailable\n";
      }
    }else{
      cout<<plate<<" is not our car\n";
    }
  }
};

int main(){
  cout<<"done\n";
}