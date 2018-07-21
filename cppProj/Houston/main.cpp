/*
v0.8
*/
#include <Engine1.h>
#include <Engine3.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
using namespace std;

static char tokenizeCmd(vector<string> & words){
    string line;
    getline(std::cin, line);
    if (cin.eof()) return 'e'; //end of input
    if (line[0] == '#') return 'c'; //comments
    istringstream tmp(line);
    copy(istream_iterator<string>(tmp),
         istream_iterator<string>(), back_inserter(words));
}

static string const outfileName="output.csv";

int main(){
 AbstractEngine * engine = nullptr;
 while(1){
    vector<string> words;
    char status = tokenizeCmd(words) ;
    if (status == 'c') continue;
    if (status == 'e') break;

    size_t wordCount = words.size();
    if (wordCount == 0) continue;

    cout<<"[ STDIN ] received a command ------------> ";
    for(int i=0; i<wordCount; ++i) cout<<words[i]<<"   ";
    cout<<endl;
    
    if (words[0] == "use" && words.size() == 2){
      if       (words[1] == "Engine1"){
        engine = new Engine1();
      }else if (words[1] == "Engine3"){
        engine = new Engine3();
      }else{
        assert(false && "USE command has typo!");
      }
    }else if (words[0] == "nextTickFile" && words.size() == 2){
	    engine->tickfile(words[1]);
    }else if(words[0] == "stats" && words.size() == 1){
      ofstream outfile(outfileName, std::ofstream::out);
	    engine->printAscending(outfile);
      outfile.close(); 
    }else if(words[0] == "verify" && words.size() == 1){
      ifstream infile(outfileName);      
	    engine->simpleTest(infile);
      infile.close();
    }else{
      cout<<"command unsupported at the moment\n";
    }
 }
 delete engine;
}
