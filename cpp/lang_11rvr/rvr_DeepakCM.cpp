/* 
showcase no-arg ctor = default
*/
#include <iostream>
#include <string>
class Employee{
  std::string name;
public:
  Employee() = default; //needed
  Employee(const Employee & s); 
  Employee(const std::string & n); 
  Employee(Employee && e);
  Employee & operator = (Employee && e); 
  Employee & operator = (const Employee & e);
  friend std::ostream & operator << (std::ostream & os, const Employee & e); 
};
Employee::Employee(const Employee & s){
  std::cout << "Copy Constructor" << std::endl;
  name = s.name;
}
Employee::Employee(const std::string & s){
  std::cout << "string (default) Constructor" << std::endl;
  name = s;
}
Employee::Employee(Employee && e){
std::cout << "Move Constructor" << std::endl;
name = e.name;
}
Employee & Employee::operator = (Employee && e){
  std::cout << "Move Assignment Operator" << std::endl;
  name = e.name;
  return *this;
}
std::ostream & operator << (std::ostream & os, const Employee & e){
  os << "Name : " << e.name << std::endl; 
  return os;
}
Employee & Employee::operator = (const Employee & e){
  name = e.name;
  return *this;
}
Employee func(){
  Employee e("Jack Sparrow");
  return e;
}
Employee func2(){
  Employee f("James Bond");
  return f;
}
int main(){
  Employee e;
  e = func();   //In this case, Move Assignment Operator is called 
  std::cout << e << std::endl;

  Employee fmove( std::move( func2() ) );   //If std::move() is called to func2(), move Constructor is called, because RVO is now suppressed
  Employee f(func2() );     //In this case, Default Constructor is called  
  std::cout << f  << std::endl;

  //Again Default constructor is called, unless we use std::move while passing Employee Object 
  Employee g(  Employee("Eathan Hunt") );   
  std::cout << g << std::endl;
}