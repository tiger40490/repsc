#include "Photon.h"
#include "utils.h"
#include "dumper.h"

using namespace std;

Grid grid = {4, {}};


void test2deflections(){ // tested 1
  Photon photon = {{5,3}, {-1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,4},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
}
void testScenario_Y(){ // tested 1
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,3},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
}
void testScenario_T(){ 
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,2},1});
  mirrors.push_back({{2,3},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
}
void testScenario_TOE(){ // 
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{1,1},1});
  mirrors.push_back({{1,2},1});
  mirrors.push_back({{1,3},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
}
void testScenario_E(){ // 
  Photon photon = {{2,5}, {0,-1}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{1,4},1});
  mirrors.push_back({{3,4},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
}
int main(){
  testScenario_E(); 
  //testScenario_TOE(); 
  //testScenario_T(); 
  //testScenario_Y();
  //test2deflections();
}