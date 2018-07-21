/*todo: handle embeded space
*/

#include <AbstractEngine.h>
#include <fstream>
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
      istringstream(line)>> tstamp >> symbol >> qty >> px;
      cout<<"new tick: "<<tstamp<<" symbol = "<<symbol<<", qty = "<<qty<<", px = "<<px<<endl;
      //create or update record 
      this->save1tick(symbol, tstamp, qty, px);
    }
    
    return '0'; //0 means success, other values can be used to indicate error
}  
