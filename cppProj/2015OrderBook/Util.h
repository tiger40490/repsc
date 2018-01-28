#ifndef UTIL_H_
#define UTIL_H_

#include <cstdlib>
#include <cstdio>
#include <cmath>
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

#define MM(x) cout<<x<<endl
#define DC if (DEBUG) cout
#define DEBUG true

using namespace std;

void dumpDTO(vector<char const *> const & v) {
	cout<<"DTO:";
	copy(v.begin(), v.end(), ostream_iterator<char const *> (cout, "|"));
	cout << endl;
}
#endif /* UTIL_H_ */
