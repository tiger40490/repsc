// v1.0
#include <Field.h>
#include <iostream>
using namespace std;

map<std::string, std::shared_ptr<Field> > Field::lookup;

Field const & Field::get(string const & name){
  if (lookup.find(name) == lookup.end()){
  	shared_ptr<Field> tmp (new Field(name));
        lookup[name] = tmp;
  	//cout<<name<<"\t: new field name added... field lookup registry size = " <<lookup.size()<<endl;
  	return *tmp;
  }
  return *lookup[name];
}
