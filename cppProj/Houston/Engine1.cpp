#include <Engine1.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <locale>
using namespace std;

char Engine1::tickfile(std::string const & filename ) {
  cout<<"Engine1 tickfile() "<<filename<<endl;
  ifstream infile(filename.c_str());
  string line, symbol;
  long long tstamp, qty;
  unsigned int px;
  while (std::getline(infile, line)) {
    if (line[0] == '#') continue;
    replace(line.begin(), line.end(), ',', ' ');
    istringstream(line)>> tstamp >> symbol >> qty >> px;
    cout<<"new tick: "<<tstamp<<" symbol = "<<symbol<<", qty = "<<qty<<", px = "<<px<<endl;
  }
  return '0'; //0 means success
}
