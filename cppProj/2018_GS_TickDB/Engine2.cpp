// v0.8
#include <Engine2.h>
#include <fstream>
#include <string>
#include <locale>
using namespace std;

//This version is very similar to Engine1, except the addition of the symbol2field2vector data store
char Engine2::tickfile(std::string const & filename ) {
  cout<<"Engine2 tickfile() "<<filename<<endl;
  ifstream infile(filename.c_str());
  string line;
  while (std::getline(infile, line)) {
    if (line[0] == '#') continue;
    istringstream iss(line);
    iss.imbue(locale(cin.getloc(), new comma_is_space));

    string symbol, fname;
    int tstamp;
    double val;
    iss >> tstamp >> symbol;
    //cout<<"new tick: "<<tstamp<<" symbol = "<<symbol<<endl;
    Tick const * tick = Tick::newTick(tstamp, symbol);

    // now we save the tick pointer in two data stores
    // #1: the per-symbol data store
    bigMap[symbol].push_back(tick);

    // #2: the per-symbol-per-field data store
    while (iss >> fname >> val) { 
      tick->addField(fname, val);
      symbol2field2vector[symbol][fname].push_back(tick);
    } 
    //cout<<*tick<<endl; //dump entire tick for debugging
  }
  // now show some stats for debugging
  getSymbolsInBigMap();
  cout<<"== per-field tick stores == "<<endl;
  for (String2vectorType::iterator itr = symbol2field2vector.begin(); itr!=symbol2field2vector.end(); ++itr){
      cout<<itr->first<<" has "<<itr->second.size()<<" per-field tick stores -- ";
      for (String2VectorType::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
        cout<<it->first<<":"<<it->second.size()<<"  ";
      cout<<endl;
  }
  cout<<"=========================== "<<endl;
  return '0'; //0 means success
}


char Engine2::product (unsigned int const ts1, 
                       unsigned int const ts2, 
                       std::string const & symbol, 
                       std::string const & fieldA , 
                       std::string const & fieldB ){
  if (bigMap.find(symbol) == bigMap.end()){
        cout<<symbol<<"  is an unknown symbol. Below are the known symbols:"<<endl;
        getSymbolsInBigMap();
        return 'u'; //unknown symbol
  }

  String2VectorType & perSymbol = symbol2field2vector[symbol];
  if (perSymbol.find(fieldA) == perSymbol.end() ){
    cout<<fieldA<<" doesn't exist for "<<symbol<<endl;
    return 'f'; //bad field;
  }
  if (perSymbol.find(fieldB) == perSymbol.end()){
    cout<<fieldB<<" doesn't exist for "<<symbol<<endl;
    return 'f'; //bad field;
  }

  vector<Tick const*> const & vecA = perSymbol[fieldA];
  int posA1, posA2; //to be populated by bsearch2
  Tick::bsearch2(vecA, posA1, posA2, ts1, ts2, symbol+":"+fieldA);
  int countA = posA2-posA1+1;
  if (countA == 0) return '0';

  vector<Tick const*> const & vecB = perSymbol[fieldB];
  int posB1, posB2; //to be populated by bsearch2
  Tick::bsearch2(vecB, posB1, posB2, ts1, ts2, symbol+":"+fieldB);
  int countB = posB2-posB1+1;
  if (countB == 0) return '0';

  double valA, valB, ret = 0;

  if (countA <= countB){ //FieldA data set is smaller, so we will ignore FieldB's vector
    for(int i=posA1; i<= posA2; ++i){ 
      if (vecA[i]->lookupField(fieldB, valB)){ //FieldB exists in this tick
	vecA[i]->lookupField(fieldA, valA);
        ret += valA*valB;
	cout<<*vecA[i]<<" is a qualified Tick"<<endl;
      }
    }
  }else{
    for(int i=posB1; i<= posB2; ++i){
      if (vecB[i]->lookupField(fieldA, valA)){
	vecB[i]->lookupField(fieldB, valB);
        ret += valA*valB;
	cout<<*vecB[i]<<" is a qualified Tick"<<endl;
      }
    }
  }
  cout<< "sum of product is "<<ret<<endl;
  return 's';
}
