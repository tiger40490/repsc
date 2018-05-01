#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char* argv[]){
  if (ifstream(argv[1]))
    cout<<argv[1]<<" exists :)\n";
  else
    cout<<argv[1]<<" isn't a relative or abs path to any File or dir :(\n";
}
