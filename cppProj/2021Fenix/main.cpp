/*
showcase RAIIBoundaryPrinter
*/
#include "Photon.h"
#include "utils.h"
#include "dumper.h"
using namespace std;

struct RAIIBoundaryPrinter{
  RAIIBoundaryPrinter() { ss<<"\t vvvvvvvvv   new test  vvvvvvvvvvv \n"; }
  ~RAIIBoundaryPrinter(){ ss<<"\t ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n"; }
};
void test2deflections(){ // tested 1
  RAIIBoundaryPrinter p;
  Grid grid = {4}; 
  Photon photon = {{5,3}, {-1,0}, grid}; // 
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,4},1});
  grid.initPrintable();
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{4,2}")); //
  assert(grid.mirrorCnt() == 0);
}
void testScenario_Y(){ // tested 1
  RAIIBoundaryPrinter* p=new RAIIBoundaryPrinter;
  Grid grid = {4}; 
  Photon photon = {{2,0}, {0,1}, grid}; 
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.push_back({{1,3},  2});
  mirrors.push_back({{3,3},1});
  mirrors.push_back({{4,2},2}); // irrelelvant now
  grid.initPrintable();
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{2,1}")); //
  assert(grid.mirrorCnt() == 2);
  delete p;
  ///////////////
  RAIIBoundaryPrinter p2;
  grid.clearBreadcrumb();
  //ss<<"same ray again\n";
  Photon photon2 = {{2,0}, {0,1}, grid}; //  same ray again, now 
  ss<<mirrors<<" ... are the surviving mirrors\n";
  lastCell = photon2.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("")); //
  assert(grid.mirrorCnt() == 1);  
}
void testScenario_T(){ 
  RAIIBoundaryPrinter p;
  Grid grid = {4}; 
  Photon photon = {{0,2}, {1,0}, grid}; // 
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.push_back({{2,1},  2});
  mirrors.push_back({{2,2},1});
  mirrors.push_back({{2,3},1});
  grid.initPrintable();
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("")); //absorbed
  assert(grid.mirrorCnt() == 2);
  /////////////
  Photon photon2 = {{0,2}, {1,0}, grid}; // same ray again, now ScenarioY 
  ss<<mirrors<<" ... are the surviving mirrors\n";
  lastCell = photon2.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{1,2}")); // reversed
  assert(grid.mirrorCnt() == 1); // last mirror had longest lifespan
  /////////////
  Photon photon3 = {{0,2}, {1,0}, grid}; // same ray again, now Scenario/
  ss<<mirrors<<" ... are the surviving mirrors\n";
  lastCell = photon3.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{1,4}")); // deflected
  assert(grid.mirrorCnt() == 0); // 
}
void testScenario_TOE(){ 
  RAIIBoundaryPrinter p;
  Grid grid = {4}; 
  Photon photon = {{0,2}, {1,0}, grid}; // 
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.push_back({{1,1},111});
  mirrors.push_back({{1,2},1});
  //mirrors.push_back({{1,3},1});
  grid.initPrintable();
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("")); //absorbed
  assert(grid.mirrorCnt() == 1);
  assert(grid.survivors.front().ttl == 111 );
}
void testScenario_E(){ // Scenario Edge, but not T-on-Edge 
  RAIIBoundaryPrinter p;
  Grid grid = {4}; 
  Photon photon = {{2,5}, {0,-1}, grid}; // 
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.push_back({{1,4},1});
  mirrors.push_back({{3,4},1});
  grid.initPrintable();
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{2,4}")); //
  assert(grid.mirrorCnt() == 0);
  //////////////
  ss<<"same ray again ...\n";
  Photon photon2 = {{2,5}, {0,-1}, grid}; // same ray again, now ScenarioY 
  ss<<mirrors<<" ... are the surviving mirrors\n";
  lastCell = photon2.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{2,1}")); // unobstructed
  assert(grid.mirrorCnt() == 0);  
}
/* This function does not logically belong to any class... was moved out of Grid class, in order to remove Grid dependency on Photon i.e. cross-dependency.
*/
std::string parse1ray(std::string ray, Grid & grid){
      //ss<<ray<<"\n";
      size_t sz = ray.size();
      char rc = ray[0];
      char sign = ray[sz-1];
      assert ( sign == '+'||'-' == sign);
      Coordinate_t numA= sign=='+'? 0 : 
        grid.length+1 ; //just outside the grid edge
      Coordinate_t numB= std::stoi(ray.substr(1, sz-2));
      if (rc=='C') std::swap(numA, numB);
      Cell photonStart = {numB, numA};
      //ss<<numB<<"=num, rc="<<rc<<"\n";
      //ss<<photonStart<<"\n";
      
      // now construct the Step object
      int intA=0;
      int intB=   sign=='+'? 1:-1;
      if (rc=='C') std::swap(intA, intB);
      Step firstStep = {intA, intB};
      
      // now construct the photon
      Photon photon = {photonStart, firstStep, grid};
      ss<<"   vvv   "<<ray<<"   vvv  "<<photon<<"\n";
      //string const & lastCell = photon.roundTrip();
      return photon.roundTrip();
}

void test2files(){
  RAIIBoundaryPrinter p;
  //Grid grid; //... 

  string mirrorsFileContent ="\n#adsfa\n8\n3 2\n3 7\n6 4\n8 7 10"; 
  string testsFileContent ="C7+\nC5+\nR5-\nC6-\nR1+";
  // Above are test data that can be two files, but for a quick test I prefer string literals.
  
  Grid & grid = *Grid::parse2files(mirrorsFileContent, testsFileContent);
  for (auto & aPair: grid.fullOutputToPrint){
    aPair.second // test result
      = parse1ray(aPair.first, grid);
  }
  grid.dumpFullOutputToStdErr();
}
int main(){
  //testScenario_TOE(); return 0;
  testScenario_Y(); return 0;
  ///testScenario_T(); return 0;
  testScenario_E(); return 0;
  test2deflections(); //return 0;
  //test2files();
}