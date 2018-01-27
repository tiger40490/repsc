// v0.8
#include <Engine1.h>
#include <Tick.h>
#include <fstream>
#include <string>
#include <locale>
using namespace std;

void Engine1::getSymbolsInBigMap(){ //utility function, non-virtual
  cout<<bigMap.size()<<" symbol(s) in the big map"<<endl; 
  for (String2VectorType::iterator it = bigMap.begin(); it!=bigMap.end(); ++it){
	cout<<it->first<<"\t tick count = "<<it->second.size()<<endl;
  }
} 

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
    //cout<<"new tick: "<<tstamp<<" symbol = "<<symbol<<endl;
    Tick const * tick = Tick::newTick(tstamp, symbol);
    bigMap[symbol].push_back(tick);

    while (iss >> fname >> val) { 
      tick->addField(fname, val);
    } 
    //cout<<*tick<<endl; //dump entire tick for debugging
  }
  this->getSymbolsInBigMap();
  return '0'; //0 means success
}


char Engine1::print  (unsigned int const ts1,
                      unsigned int const ts2, std::string const & symbol ){
  if (bigMap.find(symbol) == bigMap.end()){
	cout<<symbol<<"  is an unknown symbol. Below are the known symbols:"<<endl;
	getSymbolsInBigMap();
	return 'u'; //unknown symbol
  }
  vector<Tick const*> const & vec = bigMap[symbol];
  int pos1, pos2; //starting and ending indices to be populated
  if ('s' != Tick::bsearch2(vec, pos1, pos2, ts1, ts2, symbol))
    return '0'; // no qualifying tick

  for (size_t i = pos1; i <= pos2; ++i){
    cout<<*vec[i]<<endl;
  }
  return 's'; //s means success
}

// This version of the product() query is similar to the print() query, using the same data store
// If 99% of the ticks within the specified time window don't have both fieldA and fieldB, 
// then we waste lots of time. Engine2 has a bigger design for this scenario
char Engine1::product (unsigned int const ts1, 
                       unsigned int const ts2, 
                       std::string const & symbol , 
                       std::string const & fieldA , 
                       std::string const & fieldB ){
  if (bigMap.find(symbol) == bigMap.end()){
	cout<<symbol<<"  is an unknown symbol. Below are the known symbols:"<<endl;
	getSymbolsInBigMap();
	return 'u'; //unknown symbol
  }
  vector<Tick const*> const & vec = bigMap[symbol];
  int pos1, pos2;
  if ('s' != Tick::bsearch2(vec, pos1, pos2, ts1, ts2, symbol))
    return '0'; // no qualifying tick

  double valA, valB, ret=0;
  for (size_t i = pos1; i <= pos2; ++i){
    if (vec[i]->lookupField(fieldA, valA) && 
        vec[i]->lookupField(fieldB, valB)){
      ret += valA*valB;
      cout<<*vec[i]<<endl;
    }
  }
  cout<< "sum of product is "<<ret<<endl;
  return 's'; //s means success
}
