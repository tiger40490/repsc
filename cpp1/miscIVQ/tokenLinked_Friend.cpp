#include <iostream>
#include <vector>
#include <list>
#include <set> //faster than unordered_* for small sample
#include <map> //faster than unordered_* for small sample
#include <cassert>
#define ss if(1>0) cout
using namespace std;
typedef int Tokn;
typedef int Fren;
typedef set<Fren> Group; //group of connected friends
typedef list<Group> GoG;  //all groups owning a single token
ostream & operator<<(ostream & os, Group const & li){
  if (li.empty()){
    os<<"-";
    return os;
  }
  os<<*(li.begin());
  for(auto it=next(li.begin()); it!=li.end(); ++it){ os<<','<<*it; }
  return os;
}
ostream & operator<<(ostream & os, GoG const & li){
  if (li.empty()){
    os<<"--";
    return os;
  }
  os<<*(li.begin());
  for(auto it=next(li.begin()); it!=li.end(); ++it){ os<<"  ;  "<<*it; }
  return os;
}
int maxTokens(int fCnt, vector <int> friends_from, vector <int> friends_to, vector <int> friends_weight) {
  map<Tokn, GoG > byToken;
  ///// Step 1: populate groups, defined as a connect set of friends. Each token is shared by 1 or more groups.
  for (size_t i=0; i<friends_to.size(); ++i){
    Tokn tok = friends_weight[i];
    Fren f1 = friends_from[i];
    Fren f2 = friends_to[i];
    GoG & groups = byToken[tok];
    //look for any group to join
    bool isFound = false;
    for (auto git = groups.begin(); git != groups.end(); ++git){
      if (git->count(f1)){
        git->insert(f2);
        isFound = true;
      }
      if (git->count(f2)){
        git->insert(f1);
        isFound = true;
      }
      //todo: merge two groups if needed
      if (isFound){
        ss<<*git<<" is the expanded group\n";
        break;
      }
    } //for
    if (!isFound){
        Group newGroup = {f1, f2};
        groups.push_back(newGroup);
    }
    ss<<tok<<" (token): "<<f1<<","<<f2<<" ==> " <<byToken[tok]<<endl;
  }
  for (auto it=byToken.begin(); it!=byToken.end(); ++it){
      ss<<it->first<<" owned by "<<it->second<<endl;
  }

  ///// Step 2: update the matrix using byToken
  set<Tokn> mat[fCnt][fCnt]; //init the matrix of friendships
  for (auto it=byToken.begin(); it!=byToken.end(); ++it){
    for (auto git = it->second.begin(); git != it->second.end(); ++git){
      vector<Fren> v(git->begin(), git->end()); //a group
      //for every paring in the group, update matrix
      for (int i=0; i<v.size(); ++i) for (int j=i+1; j<v.size(); ++j){
          Fren f1=v[i], f2=v[j];
          Tokn tok = it->first;
          ss<<tok<<" (token) : linking "<<f1<<","<<f2<<endl;
          mat[f1-1][f2-1].insert(tok);
      }
    } //2nd for loop
  } //outer for loop
  for (int r=0; r<fCnt; ++r){ //instrumentation
    for (int c=0; c<fCnt; ++c) ss<<mat[r][c]<<"\t"; 
    ss<<endl;
  }
  //iterate over the matrix to find the cells with maximum number of tokens
  int maxTokensInOnePair=0, ret=0;
  for (int r=0; r<fCnt; ++r) for (int c=0; c<fCnt; ++c){
      auto cnt = mat[r][c].size();
      if (maxTokensInOnePair < cnt){
        maxTokensInOnePair = cnt;
        ret = (r+1) * (c+1);
      }else if (maxTokensInOnePair == cnt){
        int tmp = (r+1) * (c+1);
        if (ret < tmp) ret = tmp;
      }
  }
  return ret;
}
int main() {
    assert(6  == maxTokens(4, {1,1,2,2,2},
                              {2,2,3,3,4},
                              {1,2,1,3,3}));                              
    assert(3  == maxTokens(3, {1,1,2},
                              {3,3,3},
                              {1,2,2}));
    assert(20 == maxTokens(5, {1,2,4,1,4,2,2}, 
                              {2,3,5,2,5,3,4}, 
                              {1,1,1,2,2,3,3}));
}/*Req: https://wp.me/p74oew-5b5
*/
