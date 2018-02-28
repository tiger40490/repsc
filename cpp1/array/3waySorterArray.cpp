/*
showcase: typedef for readability
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#define ss if(1>0)cout
using namespace std;

typedef unsigned int Item;
typedef char Category;
typedef int Index;
Index const UNSET = 0; // must be this value
vector<Item> li;
Index cur, pL, pM, pN;
// cur is first Item in unclassified section
// pL is first Item after L section unless pL == UNSET
// pM is first Item after M section unless pM == UNSET
// pN is first Item after N section unless pN == UNSET

Category getCategory(Item i){
  if (i < 10) return 'L';
  if (i < 100) return 'M';
  if (i < 1000) return 'N';
  return 'H'; //highest Category
}
void dump(){
        for(auto it=li.begin(); it!=li.end(); ++it) ss<<*it<<" ";
        ss<<"- ";

        if(cur == li.size()) cout<<"end()";
        else                cout<<li[cur];
        ss<<" <-cur, ";

        if(pL == UNSET) cout<<"UNSET";
        else if(pL == cur) cout<<"cur";
        else cout<<li[pL];
        ss<<" <-pL, ";

        if(pM == UNSET) cout<<"UNSET";
        else if(pM == cur) cout<<"cur";
        else cout<<li[pM];
        ss<<" <-pM, ";

        if(pN == UNSET) cout<<"UNSET";
        else if(pN == cur) cout<<"cur";
        else cout<<li[pN];
        ss<<" <-pN\n";
}
bool swp(Index a, Index b){
  if (a == b || li[a] == li[b]){ return true; }
  Item tmp = li[a]; li[a] = li[b]; li[b] = tmp;
  return false;
}
void initPointers(){
  cur=0; pL=pM=pN=UNSET; //reset
  for(Index i=0; i<li.size(); ++i){
    if(getCategory(li[i]) == 'L'){
      swp(0,i);
      pL=1;
      break;
    }
  }
  for(Index i=0; i<li.size(); ++i){
    if(getCategory(li[i]) == 'M'){
      swp(pL, i); //pL could be UNSET
      pM=pL+1;
      break;
    }
  }
  for(Index i=0; i<li.size(); ++i){
    if(getCategory(li[i]) == 'N'){
      auto tmp = max(pL, pM);
      swp(tmp, i); //tmp could be UNSET
      pN=tmp+1;
      break;
    }
  }
  cur=max({pL,pM,pN});
  //ss<<"After initPointers() pL = "<<pL<<", pM = "<<pM<<", pN = "<<pN<<".. "; dump();
}
bool swapN(){
  assert(pN >= 0);
  assert(getCategory(li[cur]) == 'N');
  bool ret = swp(pN, cur);
  ++pN;
  return ret;
}
bool swapM(){
  assert(pM >= 0);
  assert(getCategory(li[cur]) == 'M');
  bool ret = swp(pM, cur);
  ++pM;
  return ret;
}
bool swapL(){
  assert(pL >= 0);
  assert(getCategory(li[cur]) == 'L');
  bool ret= swp(pL, cur);
  ++pL;
  return ret;
}
void run(vector<Item> _tmp){
  li = _tmp;
  if (li.size()<=1){ //This algo may support this edge case, but I won't bother to check
    cout<<"Input array doesn't have 2 or more items\n";
    return;
  }
  initPointers();
  if (pL == UNSET && pM == UNSET && pN == UNSET){
    cout<<"All-H... Input array needs no change.\n";
    return;
  }
  for(;cur<li.size();++cur){
    while(1){
      auto cat = getCategory(li[cur]);
      //ss<<li[cur]<<"  <-cur in while-loop\n";
      if (cat=='H') break;
      if (cat=='L'){ if (swapL()) break; }
      if (cat=='M'){ if (swapM()) break; }
      if (cat=='N'){ if (swapN()) break; }
    }
    //dump();
  }
  ss<<"done: "; dump();
}
int main(){
        run( {1111,1,44,22,3333,222,7,999,1,6,88,8,888,8888,55,0} ); //
        run( {111,1,44,22,333,222,7,99,6,88,8,888,888,4} ); //L M N
        run( {105,1,4,5,305,312,7,6,9,8,708,183,0} ); // no M or H
        run( {111,888, 333,222,77,99,66,88,8,5,7,4} ); //reverse input
        run( {111,22,555,333,77,66,99,88,777,888,44} ); //no L or H
        run( {11,1,44,22,55,31,7,77,6,99,8,66,88,4,5} ); //no N or H
        run( {1,3,5,2});
        run( {10,30,53, 12});
        run( {105,305,312}); // N only
}
/*https://wp.me/p74oew-4Cj is requirement
 * First initialize the pL and pM pointers.
 * * If no L section, then pL remains UNSET.
 * * If no M sectino, then pM remains UNSET
 * Then run the main for-loop
 */
