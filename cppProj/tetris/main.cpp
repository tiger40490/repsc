//v1.0
#include "Board.h"
#include <sstream>
using namespace std;

int const process1Line(string const & s ){
	if (s.substr(0,2) == "//"){
                DC<<"full-comment line... skipped"<<endl;
                return false;
        }
	if (s.empty()) return false;

    	cout << "\n>>>>>>>>>>>> New board: " << s << endl;
        Board b; // clean board
	string tok;
	istringstream ss(s);
	while(getline(ss, tok, ',')){
            b.dropPiece(tok[0], tok[1]-'0');
	}
        const int height = b.strictHeight();
        return height;
}
int main() {
	ifstream inFile("data/input.txt");
	ofstream outFile("data/output.txt");
	string line;
	for (int i=0; std::getline(inFile, line);++i){
		outFile<<process1Line(line)<<endl;
	}
	outFile.close();
}
