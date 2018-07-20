#include <Engine1.h>
#include <fstream>
#include <string>
#include <locale>
using namespace std;

char Engine1::tickfile(std::string const & filename ) {
  cout<<"Engine1 tickfile() "<<filename<<endl;
  ifstream infile(filename.c_str());
  string line;
  while (std::getline(infile, line)) { //line length is limited by virtual memory only
    if (line[0] == '#') continue;
    istringstream iss(line);
    iss.imbue(locale(cin.getloc(), new comma_is_space));

    string symbol, fname;
    int tstamp;
    double val;
    iss >> tstamp >> symbol;
    cout<<"new tick: "<<tstamp<<" symbol = "<<symbol<<endl;
  }
  return '0'; //0 means success
}
