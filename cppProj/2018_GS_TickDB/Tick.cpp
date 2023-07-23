// v0.8
#include <Tick.h>
#include <iostream>
#include <algorithm>
using namespace std;

ostream & operator<<(ostream & os, Tick const & t){
    os<<"------ timestamp "<<t.timestamp<<" -------"<<endl<<"[  ";
    for (Tick::FieldMapType::iterator it = t.fmap.begin(); it != t.fmap.end(); ++it)
      os<<it->first->name()<<":"<<it->second<<"  ";
    os<<"]";
    //os<<endl;
    return os;
}

//output paramter "fieldValue"
bool Tick::lookupField(std::string const & name, double & fieldValue) const{
    Field const & field = Field::get(name); 
    if (fmap.find(&field) == fmap.end()) return false;
    fieldValue = fmap[&field]; 
    return true;
}
void Tick::addField(std::string const & name, double value) const{
    Field const & field = Field::get(name); 
    fmap[&field] = value; 
}

//actually the symbol parameter is for future use
Tick const * Tick::newTick(unsigned int timestamp, std::string const & symbol){
	Tick const * ret = new Tick(timestamp, symbol);
	//cout<<"Allocated a new Tick object for "<<symbol<<enl;
	return ret;
}

bool myless(Tick const * tick, unsigned int target) {
     //cout<<tick->timestamp<<" against "<<target<<endl; 
     return tick->timestamp < target;
}
bool mygreater(unsigned int target, Tick const * tick){
     //cout<<a->timestamp<<" against "<<target<<endl; 
     return tick->timestamp > target;
}

//given an ascending sequenc, returns the lowest element position that's greater or equal to target.
//Returns negative value to indicate failure.
int Tick::bsearch(std::vector<Tick const*> const & vec, unsigned int const target, bool isLowerSide = true){
  //cout<<"starting bsearch for "<<target<<endl;
  if (vec.size()  == 0){
    cerr<<"empty vector!"<<endl;
    return -1;
  }

  //for (int i = 0; i < vec.size(); ++i) cout<<vec[i]->timestamp<<endl;

  int ret;
  if (isLowerSide){
    ret =   distance(vec.begin(), 
         lower_bound(vec.begin(),vec.end(),target,   myless)
                    );
    if (ret == 0) cout<<"start time is very early!"<<endl;
  }else{
    ret =  distance(vec.begin(), 
         upper_bound(vec.begin(),vec.end(),target,   mygreater)
                    ) - 1 ;
    if (ret+1 == vec.size()) cout<<"end time is far out!"<<endl;
  }

  if (0 > ret || ret >= vec.size())  {
	cerr<<target<<" : target timestamp is outside our time range"<<endl;
	return -2; //search failure
  }
  //cout<<"returning "<<ret<<endl;
  return ret;
}

//search for both lower and upper timestamps in the same vector
char Tick::bsearch2(vector<Tick const*> const & myvec, int & pos1, int & pos2,
		unsigned int const ts1, 
		unsigned int const ts2, std::string const & identifier){
  cout<<myvec.size()<<"\t ticks exists (regardless of timestamp) in entire data store for "<<identifier<<endl;
  pos1 = Tick::bsearch(myvec, ts1, true);
  pos2 = Tick::bsearch(myvec, ts2, false);
  if (pos1 < 0 || pos2 < 0){
    cout<<"no tick qualified"<<endl;
    return 'n';
  }
  int count = pos2-pos1+1;
  cout<<count<<"\t ticks qualified for "<<ts1<<" - "<<ts2<<endl;
  if (count <= 0) return '0';
  return 's'; //success
}

