#include "Photon.h"
#include "utils.h"
#include "dumper.h"

using namespace std;

Grid grid = {4};

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
  assert(lastCell == string("{4,2}")); //
  assert(grid.mirrorCnt() == 0);
}
void testScenario_Y(){ // tested 1
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{2,1},1});
  mirrors.push_back({{2,3},1});
  mirrors.push_back({{4,4},1}); // irrelelvant
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
  assert(lastCell == string("{1,2}")); //
  assert(grid.mirrorCnt() == 1);
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
  assert(lastCell == string("")); //absorbed
  assert(grid.mirrorCnt() == 2);
}
void testScenario_TOE(){ 
  Photon photon = {{0,2}, {1,0}, grid}; // one photon
  ss<<photon<<endl;
  list<Mirror> & mirrors = grid.survivors;
  mirrors.clear();
  mirrors.push_back({{1,1},1});
  mirrors.push_back({{1,2},1});
  //mirrors.push_back({{1,3},1});
  ss<<mirrors<<" ... are the initial mirrors\n";
  auto lastCell = photon.roundTrip();
  ss<<lastCell.c_str();
  assert(lastCell == string("")); //absorbed
  assert(grid.mirrorCnt() == 1);
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
  assert(lastCell == string("{2,4}")); //
  assert(grid.mirrorCnt() == 0);
}
std::string oneRay(std::string ray){
      ss<<ray<<"\n";
      size_t sz = ray.size();
      char rc = ray[0];
      char sign = ray[sz-1];
      assert ( sign == '+'||'-' == sign);
      Coordinate_t numA= sign=='+'? 0 : grid.length+1 ;
      Coordinate_t numB= std::stoi(ray.substr(1, sz-2));
      
      if (rc=='C') std::swap(numA, numB);
      Cell photonStart={numB, numA};
      //ss<<numB<<"=num, rc="<<rc<<"\n";
      //ss<<photonStart<<"\n";
      
      int intA=0;
      int intB= sign=='+'? 1:-1;
      if (rc=='C') std::swap(intA, intB);
      Step firstStep={intA,intB};
      Photon photon={photonStart,firstStep, grid};
      ss<<photon<<"\n";
      string const & lastCell = photon.roundTrip();
      ss<<lastCell;
      return lastCell;
}

void testParse(){
  string mirrors ="\n#adsfa\n8\n3 2\n3 7\n6 4\n8 7 10";
  string tests ="C7+\nC5+\nR5-";
  grid.parse2files(mirrors, tests);
  for (auto & aPair: grid.fullOutputToPrint){
    aPair.second = oneRay(aPair.first);
  }
  grid.dumpFullOutputToStdErr();
}
int main(){
  //testScenario_E(); 
  //testScenario_TOE(); 
  //testScenario_T(); 
  //testScenario_Y();
  //test2deflections();
  testParse();
}