#include <vector>
#include <iostream>
using namespace std;

struct Student{
  Student & operator=(Student const &){
    cout<<"op=() called\n";
    return *this;
  }
  Student(Student const &){
    cout<<"copy-ctor called\n";    
  }
  Student(char c){
    cout<<c<<" <-- char passed to conversion-ctor\n";
  }
};
int main(){
  vector<Student> empty;
  vector<Student> populated{'x', 'y', 'z'};
  cout<<"now assigning populated vector to empty vector...\n";
  
  empty = populated; //Probably using in-place copy-construct for each Student
  cout<<empty.size()<<" is new size of 'empty' \n";
}