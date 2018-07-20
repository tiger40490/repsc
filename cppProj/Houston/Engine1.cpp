#include <Engine1.h>
#include <fstream>
#include <string>
#include <locale>
using namespace std;

char Engine1::tickfile(std::string const & filename ) {
  cout<<"Engine1 tickfile() "<<filename<<endl;
  ifstream infile(filename.c_str());
  string line;
  while (std::getline(infile, line)) {
    if (line[0] == '#') continue;
    istringstream iss(line);
    iss.imbue(locale(cin.getloc(), new comma_is_space));

    string symbol;
    long long tstamp, qty;
    unsigned int px;
    iss >> tstamp >> symbol >> qty >> px;
    cout<<"new tick: "<<tstamp<<" symbol = "<<symbol<<", qty = "<<qty<<", px = "<<px<<endl;
  }
  return '0'; //0 means success
}
