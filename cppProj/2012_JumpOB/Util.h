#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <assert.h>

#ifndef UTIL_H_
#define UTIL_H_
using namespace std;

void dump1(vector<char const *> const & v) {
	cout<<"vec<s>=";
	copy(v.begin(), v.end(), ostream_iterator<char const *> (cout, "|"));
	cout << endl;
}
//vector<string> const & tokenize(const string & line) {
//	std::stringstream lineStream(line);
//	std::string token;
//	vector<string> tmp_vec;
//	while (std::getline(lineStream, token, ',')) {
//		tmp_vec.push_back(token);
//	}
//	dump1(tmp_vec);
//	return tmp_vec;
//}
#endif /* UTIL_H_ */
