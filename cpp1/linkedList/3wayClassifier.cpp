/*
list::erase() silently invalidates any iterator positioned at the erased node. Therefore, it's crucial to check if we are erasing mm or hh.
*/

#include <iostream>
#include <list>
#include <assert.h>
using namespace std;

typedef int item;
list<item> li={5,3,6,1,12,6,312,4,81,6,89,8,708,183,4};
auto mm = li.begin(), hh = li.begin(), un = li.begin();
//mm is first M, hh is first H, un is first unclassified

void dump(){
	for(auto item: li) cerr<<item<<" ";
	cerr<<"- ";
	
	if(un == li.end()) cerr<<"end()";
	else cerr<<*un;
	cerr<<" <-un, ";
	
	if(mm == li.end()) cerr<<"end()";
	else if(mm == un) cerr<<"un";
	else cerr<<*mm;
	cerr<<" <-mm, ";

	if(hh == li.end()) cerr<<"end()";
	else if(hh == un) cerr<<"un";
	else cerr<<*hh;
	cerr<<" <-hh\n";
}

void reorg(){
	for (; un != li.end();){
		dump();
		item a = *un;
		if (a < 10){ //L item
			{ if (un == mm) ++mm;
			  if (un == hh) ++hh;
			  un = li.erase(un);		
			}
			li.insert(mm, a);
			cerr<<a<<" moved to before mm\n";
			continue;
		}
		if(a < 100){ // M item
			{ if (un == hh) ++hh;
			  un = li.erase(un);
			}
			li.insert(hh, a);
			cerr<<a<<" moved to before hh. Before this move, mm ptr was not necessarily at first Medium item\n";
			continue;
		}
		++un;
		cerr<<"un incremented. Until this increment, hh ptr was not necessarily at first High item\n";
	}
}

int main(){
	reorg();
	dump();
}
/*https://bintanvictor.wordpress.com/?p=17751&preview=true
*/