/*
showcase: check file existence
showcase: check file size 
*/
#include <iostream>
#include <fstream>
using namespace std;
int main(){
  size_t const mb = 20;
  string fullpath= "./" + to_string(mb) + "MB_diskHogMade]cpp.dat";
  if (ifstream(fullpath)){
    cout<<fullpath<<" will be overwritten ..\n";
  }
  ofstream outfile(fullpath);
  for(auto i=0; i<mb*1024*1024; ++i) outfile<<'.';
  outfile.close();
  
  ifstream tmp2(fullpath);
  tmp2.seekg(0, ios_base::end); //will return size 0 without this
  cout<<fullpath<<" created with "<<tmp2.tellg()<<" bytes.\n";
}
