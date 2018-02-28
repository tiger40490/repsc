/*Warning: list::erase() silently invalidates any iterator positioned at the erased node. Therefore, it's crucial to check if we are erasing mm or hh.
showcase: typedef for readability
*/
#include <iostream>
#include <list>
#include <assert.h>
using namespace std;
typedef int item;
list<item> li={5,111,12,6,312,4,81,6,89,8,708,183,4};
auto mm = li.begin(), hh = li.begin(), un = li.begin();
// mm is first item in M section,
// hh is first item in H section,
// un is first item in unclassified section
// if hh equals un, it means there's no real H section.
void dump(){
        for(auto it=li.begin(); it!=li.end(); ++it) cerr<<*it<<" ";
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
void reshuffle(){
        for (; un != li.end();){
                cout<<">> ";
                dump();
                item val = *un;
                if (val < 10){ //L item
                        { if (un == mm) ++mm;
                          if (un == hh) ++hh;
                          un = li.erase(un);
                        }
                        li.insert(mm, val);
                        cerr<<val<<" moved to before mm\n";
                        continue;
                }
                if(val < 100){ // M item
                        { if (un == hh) ++hh;
                          un = li.erase(un);
                        }
                        auto inserted = li.insert(hh, val);
                        if(hh == mm) mm=inserted;
                        cerr<<val<<" moved to before hh. Before this move, mm ptr was not necessarily at first Medium item\n";
                        continue;
                }
                ++un;
                cerr<<"un incremented. Until this increment, hh ptr was not necessarily at first High item\n";
        }
}
int main(){
        reshuffle();
        dump();
}
/*https://wp.me/p74oew-4Cj is requirement */
