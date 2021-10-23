#include "Photon.h"
#include "utils.h"
#include "dumper.h"

using namespace std;

Grid grid = {5, {}};

void testMove1(){
  Photon photon = {{1,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,2},1});
  //ss<<photon.distanceTo(mirrors.back()); return;
  mirrors.push_back({{2,3},1});
  ss<<mirrors;
  photon.move1step();
}

int main(){
  testMove1();
}