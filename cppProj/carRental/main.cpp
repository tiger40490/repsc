// todo: more tests
//showcase: get current time as string
//showcase: c++11 enum class
//showcase: c++ type alias
//showcase: map and set of shared_ptr. Use temp variables to separate construction and insert
#include <assert.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory> //shared_ptr
using namespace std;
using AvailableCount = size_t; //same as typedef
enum class Brand {BMW, Ford};

class Car{ //
  string const plate; //license
  Brand  const brand;
  bool _isAvailable; // not in workshop or rented out
  vector<string> trips; 
  vector<string> repairs; // not in use
public:
  Car(string const & p, Brand const & b): plate(p), brand(b), _isAvailable(true){
    assert (this->plate.size() > 0 && "plate must be non-empty");
  }
  virtual ~Car(){cout<<this->plate<<" dtor called\n"; }
  string const & getPlate()   const{ return this->plate; } 
  Brand          getBrand()   const{ return this->brand; }
  bool           isFree()  const{ return this->_isAvailable; }
  virtual size_t getSeatCnt() const{ return 5; }
  void markAvailable()   {this->_isAvailable = true; }
  void markUnAvailable() {this->_isAvailable = false; }  
  //friend ostream & operator<<(ostream &os, Car const& s){  }
  void startRepair() {
    time_t tmp3 = time(0);
    this->repairs.push_back("repair_started at " + string{ctime(&tmp3)});
    this->markUnAvailable();
  }  
  void endRepair() {
    time_t tmp3 = time(0);
    this->repairs.push_back("returned at " + string{ctime(&tmp3)});
    this->markAvailable();
  }
  void startTrip() {
    time_t tmp3 = time(0);
    this->trips.push_back("trip_started at " + string{ctime(&tmp3)});
    this->markUnAvailable();
  }  
  void endTrip() {
    time_t tmp3 = time(0);
    this->trips.push_back("returned at " + string{ctime(&tmp3)});
    this->markAvailable();
  }
  void printTrips() const { 
    for(auto it = trips.begin(); it != trips.end(); ++it){ 
	  cout<<*it<<" "; 
	}
    cout<<std::endl;
  }
};
class SUV: public Car{
  bool isRow3Up;
public:
  SUV(string const & p, Brand const & b, bool r3): Car(p, b), isRow3Up(r3){}
  void addRow3()   { this->isRow3Up = true;}
  void removeRow3(){ this->isRow3Up = false;}
  bool checkRow3()    const{ return this->isRow3Up;}
  size_t getSeatCnt() const{ return this->isRow3Up? 8:5; }
};
class Sedan: public Car{
  bool const isSPAdded; //sports package
public:
  Sedan(string const & p, Brand const & b, bool sp): Car(p, b), isSPAdded(sp){}
};

class CarRental {
  unordered_map<string, shared_ptr<Car> > inventory; //plate -> Car
  unordered_set<        shared_ptr<Car> > freeCars;
public:
  CarRental() {}
  AvailableCount getFreeCnt() const {return this->freeCars.size(); }
  shared_ptr<Car> findCarByPlate(string const & plate) const{
    auto const itr = inventory.find(plate);
    if (itr == inventory.end()){
      return nullptr;
    }else{
      return itr->second;
    }
  }
  AvailableCount addCar(Car const & aCar){
	Car & newCar = const_cast<Car&>(aCar);
    shared_ptr<Car> ptr{&newCar};
    this->freeCars.insert(ptr);
    string const & plate = newCar.getPlate();
    this->inventory[plate] = ptr; // simpler than insert(pair)
    return this->getFreeCnt();
  }
  AvailableCount startRental(string const & plate){
    auto carPtr = findCarByPlate(plate);
    if (carPtr) {
      if (carPtr->isFree()){
        carPtr->startTrip();
        this->freeCars.insert(carPtr);
      }else{
        cout<<plate<<" is unavailable\n";
      }
      return this->getFreeCnt();
    }
    cout<<plate<<" is not our Car\n";
    return this->getFreeCnt();
  }
  AvailableCount endRental(string const & plate){
    auto carPtr = findCarByPlate(plate);
    if (carPtr) {
      if (carPtr->isFree()){
        cout<<plate<<" is already in our garage, not rented out!\n";
       }else{
        carPtr->endTrip();
        this->freeCars.erase(carPtr);
      }
      return this->getFreeCnt();
    }
    cout<<plate<<" is not our car\n";
    return this->getFreeCnt();
  }
};

int main(){
  // populate the inventory
  // start rental
  // check setCnt
  // end rental
  // print trips
  cout<<"done\n";
}