#include "utils.h"
#include "dumper.h"

using namespace std;

list<Mirror> mirrors; // list is good for erase.
// need a way to populate it from the file

//^^^^^^^^ part of the board class

void testMove1(){
  Photon photon = {{1,2}, {1,0}}; // one photon
  ss<<photon<<endl;
  mirrors.push_back({{2,1},-1});
  mirrors.push_back({{2,3},-1});
  ss<<mirrors;
}

int main(){
/*  list<double> li={3.1, 5,2,9};
  Set<short> myset={1, 2, 42, 5};
#if (__cplusplus >= 201703L)
  vector<float> vec={3.5, 1.9, 0.8};
#else  
  vector<string> vec={"dabao", "meimei", "princess"}; //works under g++ -std=c++14 but not c++17
#endif
  Map<int, bool> tm={{11,true}, {22,false}};
  ss<<vec<<tm;
  ss<<" <-- vector and map; list and set -->\n";
  ss<<li<<myset;
  ss<<__cplusplus <<" = __cplusplus \n";
*/
  testMove1();
}