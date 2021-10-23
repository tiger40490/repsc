#include "Photon.h"
#include "utils.h"
#include "dumper.h"

using namespace std;

Grid grid = {4, {}};

void testMove1(){
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.push_back({{2,1},1});
  //mirrors.push_back({{2,2},1});
  //ss<<photon.distanceTo(mirrors.back()); return;
  mirrors.push_back({{2,3},1});
  ss<<mirrors<<" <-- the mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
}

int main(){
  //string aa ("{" + to_string(33));   ss<<aa; return 0;
  testMove1();
}