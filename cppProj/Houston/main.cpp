#include <Engine1.h>
#include <Engine3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
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

int main(){
 AbstractEngine * engine = new Engine3();
 while(1){
    vector<string> words;
    char status = tokenizeCmd(words) ;
    if (status == 'c') continue;
    if (status == 'e') break;

    size_t wordCount = words.size();
    if (wordCount < 2 ) continue;

    cout<<"[ STDIN ] received a command ------------> ";
    for(int i=0; i<wordCount; ++i) cout<<words[i]<<"   ";
    cout<<endl;

    //unsigned int ts1, ts2;
    if (words[0] == "tickfile" && words.size() == 2){
	    engine->tickfile(words[1]);
	    engine->printAscending();
    }
 }
}
