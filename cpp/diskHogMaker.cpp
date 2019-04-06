/*
showcase: check file existence
showcase: check file size 

tested for 20/100 MB
*/
#include <iostream>
#include <fstream>
using namespace std;
int main(){
  size_t const mb = 500;
  string fullpath= "./" + to_string(mb) + "MB_diskHogMade]cpp.dat";
  if (ifstream(fullpath)){
    cout<<fullpath<<" will be overwritten ..\n";
  }
  ofstream outfile(fullpath);
  int const unit=1024*1024;
  for(auto i=1; i<mb*unit+1; ++i) {
    outfile<<'.';
    if (i%(10*unit) == 0) cout<<i/unit<<" MB done"<<endl;
  }
  outfile.close();
  
  //now get file size.. reusable technique
  ifstream tmp2(fullpath);
  tmp2.seekg(0, ios_base::end); //will show size 0 without this
  cout<<fullpath<<" created with "<<tmp2.tellg()<<" bytes.\n";
}
