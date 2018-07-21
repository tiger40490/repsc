/*
Assumption: no embedded space in csv

v0.92
*/

#include <AbstractEngine.h>
#include <sstream>
using namespace std;
  
char AbstractEngine::tickfile(std::string const & filename ) {
    cout<<"Engine1 tickfile() "<<filename<<endl;
    ifstream infile(filename.c_str());
    string line, symbol;
    TStamp tstamp;
    Quantity qty;
    Price px;
    while (getline(infile, line)) {
      if (line[0] == '#') continue; //skip comment/header in input file
      replace(line.begin(), line.end(), ',', ' ');
      auto is = istringstream(line);
      is >> tstamp >> symbol >> qty >> px;
      //cout<<"new tick: "<<tstamp<<" symbol = "<<symbol<<", qty = "<<qty<<", px = "<<px<<endl;
      if ( (is.rdstate() & std::ifstream::failbit ) != 0 ){
        cerr << "Error parsing a csv line\n";
        return 'f'; //failed while parsing csv
      }
      this->save1tick(symbol, tstamp, qty, px);
    }
    return '0'; //0 means everything fine, other values can be used to indicate error
}  
void AbstractEngine::simpleTest(ifstream & infile){
  std::string line; 
  while (std::getline(infile, line)){
    if (line == "ggg,1674,100,163,171"){
      return;
    }
  }
  string errMsg = "target line not found in per-symbol statistics\n"; 
  cerr<< errMsg;
  throw errMsg;
}
