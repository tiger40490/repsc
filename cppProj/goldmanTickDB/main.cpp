// v0.9
#include <Engine2.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

char tokenize(vector<string> & words){
    words.clear(); //reuse object to reduce memory allocation
    string line;
    getline(std::cin, line);
    if (cin.eof()) return 'e'; //end of input
    if (line[0] == '#') return 'c'; //comments
    istringstream tmp(line);
    copy(istream_iterator<string>(tmp),
         istream_iterator<string>(), back_inserter(words));
}

unsigned int toTimestamp(string s){
  unsigned int ret = stoi(s);
  return ret;
}

void myexit(string s, int status = 1780){
  cerr<<"Fatal error: "<<s<<endl;
  exit(status);
}

int main(int argc, char **argv){
 if (argc > 2) {
   myexit("too many command line args");
 }
 AbstractEngine * engine;
 if (argc == 2){
   string mode = argv[1];
   //cout<<mode<<endl;

   if    (mode == "-Oproduct") engine = new Engine2();
   else if (mode == "-Oprint") engine = new Engine1();
   else myexit("invalid -O value");
 }else{
   engine = new Engine1(); //default
 }
 
 vector<string> words;
 while(1){
    char status = tokenize(words) ;
    if (status == 'c') continue;
    if (status == 'e') break;

    size_t wordCount = words.size();
    if (wordCount < 2 ) continue;

    cout<<"[ STDIN ] received a command ------------> ";
    for(int i=0; i<wordCount; ++i) cout<<words[i]<<"   ";
    cout<<endl;

    unsigned int ts1, ts2;
    if (words[0] == "tickfile" && words.size() == 2){
	engine->tickfile(words[1]);
    }else if (words[0] == "print"    && words.size() == 4){
	engine->print   (toTimestamp(words[1]), toTimestamp(words[2]), words[3]);
    }else if (words[0] == "product"  && words.size() == 6){
	engine->product (toTimestamp(words[1]), toTimestamp(words[2]), words[3], words[4], words[5]);
    }else{
	cerr<<"... invalid command from STDIN!"<<endl;
    }
 }
}
