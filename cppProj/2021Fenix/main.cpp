#include "Photon.h"
#include "utils.h"
#include "dumper.h"

using namespace std;

Grid grid = {4};
struct BlockPrinter{
  BlockPrinter() { ss<<"\t vvvvvvvvv   new test  vvvvvvvvvvv \n"; }
  ~BlockPrinter(){ ss<<"\t ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n"; }
};
void test2deflections(){ // tested 1
  BlockPrinter p;
  Photon photon = {{5,3}, {-1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,4},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{4,2}")); //
  assert(grid.mirrorCnt() == 0);
}
void testScenario_Y(){ // tested 1
  BlockPrinter p;
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,3},1});
  mirrors.push_back({{4,4},1}); // irrelelvant
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{1,2}")); //
  assert(grid.mirrorCnt() == 1);
}
void testScenario_T(){ 
  BlockPrinter p;
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,2},1});
  mirrors.push_back({{2,3},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("")); //absorbed
  assert(grid.mirrorCnt() == 2);
}
void testScenario_TOE(){ 
  BlockPrinter p;
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{1,1},1});
  mirrors.push_back({{1,2},1});
  //mirrors.push_back({{1,3},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("")); //absorbed
  assert(grid.mirrorCnt() == 1);
}
void testScenario_E(){ // 
  BlockPrinter p;
  Photon photon = {{2,5}, {0,-1}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{1,4},1});
  mirrors.push_back({{3,4},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell<<endl;
  assert(lastCell == string("{2,4}")); //
  assert(grid.mirrorCnt() == 0);
}
std::string parse1ray(std::string ray){
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
  BlockPrinter p;
  grid.survivors.clear();
  string mirrorsFileContent ="\n#adsfa\n8\n3 2\n3 7\n6 4\n8 7 10"; 
  string testsFileContent ="C7+\nC5+\nR5-";
  // Above are test data that can be two files, but for a quick test I prefer string literals.
  
  grid.parse2files(mirrorsFileContent, testsFileContent);
  for (auto & aPair: grid.fullOutputToPrint){
    aPair.second // test result
      = parse1ray(aPair.first);
  }
  grid.dumpFullOutputToStdErr();
}
int main(){
  test2deflections();
  testScenario_E(); 
  testScenario_TOE(); 
  testScenario_T(); 
  testScenario_Y();
  test2files();
}