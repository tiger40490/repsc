//showcase operator<< for VO class, as a free function, not method
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

int const UNASSIGNED = -1;
struct Node{
  char val;
  int islandId; //always above 10 or unassigned
  Node *linkU, *linkD, *linkL, *linkR;
  Node(): val(0), islandId(UNASSIGNED), 
    linkU(0),linkD(0),linkL(0),linkR(0){}
};
ostream & operator<<(ostream & os, Node const & n){
  os<<"[ ";
  os<<(n.linkL? "<-":"| "); //| means no link to Left
  os<<(n.linkU? "^ ":"u "); //u means no link Up
  os<<(int)n.val<<" Is_"<<n.islandId;
  os<<(n.linkD? " v":" d"); //d means no link Down
  os<<(n.linkR? "->":" |"); //| means no link to Right
  os<<" ]";
  return os;
}
void BFT(Node * start){ //mark all MY connected nodes with the same islandId
  if (start->islandId!=UNASSIGNED) return; //already marked
  static int iid = 10;
  bool isNewIsland=false;
  queue<Node*> q; //start new queue for each island
  q.push(start);
  while(!q.empty()){
    Node * node = q.front();
    q.pop();
    //if (node->val == 1) continue; //leave unassigned
    if (node->islandId!=UNASSIGNED) continue;
    if (node->linkU) q.push(node->linkU);
    if (node->linkL) q.push(node->linkL);
    if (node->linkR) q.push(node->linkR);
    if (node->linkD) q.push(node->linkD);
    node->islandId = iid;
    isNewIsland = true;
  }
  if (isNewIsland) ++iid;
}

/* construct directed graph connecting all the cells, by adding a link
whenever there's no wall between two adjcent cells

Designate the Jerry node as the destination.

Designate all cheese cells as must-visit nodes.

Run a constrained shortest-path algorithm.

If designation or any must-visit node is not connected to (0,0), then return Failure.
*/
int minMoves(vector<vector<int>> maze, int x, int y) {
  int const rCnt = maze.size();
  int const cCnt = maze[0].size();
  for(int r=0; r<rCnt; ++r) {
    for(int c=0; c<cCnt; ++c) cout<<maze[r][c]<<" ";
    cout<<endl;
  }
  vector<vector<Node>> nodes(rCnt);
  for (int r=0; r<rCnt; ++r){
    nodes[r].resize(cCnt);
    for(int c=0; c<cCnt; ++c){
      auto & n = nodes[r][c];
      n.val=maze[r][c];
    }
  }
  //construct graph links
  for (int r=0; r<rCnt; ++r){
    for(int c=0; c<cCnt; ++c){
      auto & n = nodes[r][c];
      if (r>0 && nodes[r-1][c].val!=1) n.linkU = &nodes[r-1][c];
      if (c>0 && nodes[r][c-1].val!=1) n.linkL = &nodes[r][c-1];
      if (c<cCnt-1 && nodes[r][c+1].val!=1) n.linkR = &nodes[r][c+1];
      if (r<rCnt-1 && nodes[r+1][c].val!=1) n.linkD = &nodes[r+1][c];
    }
  }
  //assign an id to each island to check infeasibility  i.e. -1
  for(int r=0; r<rCnt; ++r) {
    for(int c=0; c<cCnt; ++c) BFT(&nodes[r][c]);
  }
  for(int r=0; r<rCnt; ++r) {
    for(int c=0; c<cCnt; ++c) cout<<nodes[r][c]<<"   ";
    cout<<endl;
  }
  auto tomIsland = nodes[0][0].islandId;
  if (nodes[x][y].islandId != tomIsland) return -1;
  //now check the island of Jerry and all the cheese cells. If any of them is != tomIsland, then return -1
  return 0;
}
int main() {
    vector<vector<int>> maze={{1,0,1}, {0,2,2}, {1,1,0}};
    int ret = minMoves(maze, 2, 0);
    cout<<ret<<endl;
}
/* Req: https://bintanvictor.wordpress.com/2018/04/14/connected-matrix-cells-with-barriers/
*/