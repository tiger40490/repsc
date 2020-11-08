class Student:
  def __init__(self, name, age, city):
    self.name=name
    self.age=age
    self.city=city
class School:
  def __init__(self):
    self.studentInfo=dict()
  def populate(self, id, name, age, city):
    self.studentInfo[id]=Student(name,age,city)
  def printme(self):
    for k,v in self.studentInfo.items():
      print k, v.name, v.age, v.city 
# a test:
s = School()
s.populate( 1, "alice", 23, "New York" );
s.populate( 2, "brian", 24, "London" );
s.populate( 3, "claire", 21, "Paris" );
s.populate( 4, "winston", 29, "Princeton" );
s.populate( 5, "scott", 31, "Atlanta" );
s.printme();
'''
#include <iostream>
#include <string>
#include <map>
struct Student{
    std::string name;
    int age;
    std::string city;
    Student( const std::string & n, int a, const std::string & c ): name( n ), age( a ), city( c ) {}
};
typedef std::map<int, Student> StudentInfo;
class School{
    StudentInfo studentInfo;
public:
    void populate( int id, const std::string & n, int a, const std::string & c );
    void print();
};
void School::populate( int id, const std::string & n, int a, const std::string & c ){
    studentInfo.insert( std::make_pair( id, Student( n, a, c ) ) );
}
void School::print(){
    for ( auto i : studentInfo)   {
        std::cout << i.first << " -> " << i.second.name << " " << i.second.age << " " << i.second.city << "\n";
    }
}
int main(){
    School * s = new School();
    s->populate( 1, "alice", 23, "New York" );
    s->populate( 2, "brian", 24, "London" );
    s->populate( 3, "claire", 21, "Paris" );
    s->populate( 4, "winston", 29, "Princeton" );
    s->populate( 5, "scott", 31, "Atlanta" );
    s->print();
}
'''
