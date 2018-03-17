//compile with g++ -c this.file
//showcase: type alias, same as typedef
//showcase: enum class
//showcase: deleting while iterating a set
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <set> //or unordered_set
#include <list>
#include <vector>
#include <deque>
using namespace std;
using Level = unsigned short; //same as typedef

enum class BtnDir {u, d};
enum class LiftDir {u, d, none};
struct Btn{ //button in lift lobby
  Level const level;
  BtnDir direction;
  Btn(Level l, BtnDir dir): level(l), direction(dir){}
};
vector<Btn> const all_buttons={Btn(1, BtnDir::u),
Btn(2, BtnDir::u),Btn(2, BtnDir::d), Btn(3, BtnDir::u),Btn(3, BtnDir::d),
Btn(4, BtnDir::u),Btn(4, BtnDir::d), Btn(5, BtnDir::u),Btn(5, BtnDir::d),
Btn(6, BtnDir::u),Btn(6, BtnDir::d), Btn(7, BtnDir::u),Btn(7, BtnDir::d),
Btn(8, BtnDir::d)};
struct Request{
  Btn const & source;
  time_t when; //useful for priority setting
  bool completed; //can be completed by any lift L, even if not assigned to L
  
  Request(Btn const & s): source(s), when(time(0)), completed(false){}
};
bool operator<(shared_ptr<Request> const & a, shared_ptr<Request> const & b){
  //not used for priority, but to remove duplicate requests
    if (a->source.direction != b->source.direction)
      return a->source.direction < b->source.direction;
	else
  	  return a->source.level < b->source.level; 
}
struct Lift{
  int id;
  LiftDir dir;
  Level level;
  size_t passengerCnt;
  set<Level> targets; //populated by passengers inside the lift or by setTarget()
  set<shared_ptr<Request>> assignedRequests;
  
  Lift(int _id): id(_id), dir(LiftDir::none), level(1){}
  void move(); /*based on direction+level+targets and nothing else
  Note some target could be in the opposite direction but since 
  we have taken it on we will service it  */
  void addPessengerRequests(); //passengers can push buttons inside the lift to add "targets"
  void cleanupAssigned(){
    for(auto it=this->assignedRequests.begin(); it!=assignedRequests.end();)
	  if ((*it)->completed) assignedRequests.erase(it++);
	  else ++it;
  }
  bool shouldTakeOn(Request const & req) const; 
  /*based on current direction/level, decide to take on a request. Note if a request 
  has been pending for a long time we need to take it on unconditionally*/
};
vector<Lift> lifts={Lift(1), Lift(2)};
set<shared_ptr<Request>> unserviced; //whenwe take on a request, it's removed from here

int calcDuration();
bool isTerminationNeeded();
void receiveNewRequestsFromSharedBuffer(); //add new requests to unserviced and do nothing else

void assignToLifts(){
  size_t taken=0;
  for(auto it = unserviced.begin(); it!=unserviced.end(); ){
    bool isTakenOn = false;
	auto sptr=*it;
    for(auto & lift: lifts){
	   if (lift.shouldTakeOn(*sptr)){
	     unserviced.erase(it++);		 
		 lift.assignedRequests.insert(sptr);
		 isTakenOn = true;
		 ++taken;
	     break; //skip other lifts
	   }
	}
	if (!isTakenOn){
	  ++it;
  	  cout<<(sptr)->source.level<<" is unserviceable at the moment\n";
    }
  }
  cout<<taken<<" requests taken up\n";
}
int work(){
  if (isTerminationNeeded()) return -1;
  receiveNewRequestsFromSharedBuffer(); 
  assignToLifts();
  for(auto & lift: lifts){
    lift.cleanupAssigned();
	lift.addPessengerRequests();
    if(lift.targets.empty()) cout<<lift.id<<" has no target and will not move\n";
	else lift.move();
  }
}
int main(){
  int duration=1;
  for(;;){
    if (work() < 0) break;
	duration=calcDuration(); // based on lift1, unserviced 
	usleep(duration);
  }
  cout<<"requested to termination\n";
}
//Requirement https://bintanvictor.wordpress.com/2018/03/16/elevator-design/