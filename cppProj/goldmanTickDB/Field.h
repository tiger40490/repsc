// v1.0
#ifndef FIELD_H
#define FIELD_H 1
#include <string>
#include <map>
#include <memory>

class Field {
  
  //There are a large number of non-unique field names mentioned in a tick file.
  //To save memory, I allocate memory for each globally unique field name once only.
  //If there are 50 unique field names in a tick file, we only have 50 Field objects 
  //referenced by many shared_ptr objects.
  //
  //For this lookup, A hash table is possibly faster (if map is large) but not really 
  //in some benchmark tests. Our map size is assumed to be small, like 100
  static std::map<std::string, std::shared_ptr<Field> > lookup;


  std::string const field_name;
  
  Field(std::string const & s): field_name(s){}
  Field(Field const &);
  Field & operator=(Field const &);

public: 
  std::string const & name() const {
    return this->field_name;
  }

  // if the name is new, add it to the registry and return a reference to the Field object
  // if the name is known, return a reference
  static Field const & get(std::string const & newOrKnown);
};
#endif

