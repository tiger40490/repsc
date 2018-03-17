// g++ -c this.file
//showcase: c++11 type alias, same as typedef
//showcase: c++11 enum class
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
struct lobbyBtn{ //button in lift lobby
  Level const level;
  BtnDir direction;
  lobbyBtn(Level l, BtnDir dir): level(l), direction(dir){}
};
vector<lobbyBtn> const all_buttons={lobbyBtn(1, BtnDir::u),
lobbyBtn(2, BtnDir::u),lobbyBtn(2, BtnDir::d), lobbyBtn(3, BtnDir::u),lobbyBtn(3, BtnDir::d),
lobbyBtn(4, BtnDir::u),lobbyBtn(4, BtnDir::d), lobbyBtn(5, BtnDir::u),lobbyBtn(5, BtnDir::d),
lobbyBtn(6, BtnDir::u),lobbyBtn(6, BtnDir::d), lobbyBtn(7, BtnDir::u),lobbyBtn(7, BtnDir::d),
lobbyBtn(8, BtnDir::d)};

struct Request{ //requests from lift lobbies, not "targets" set by in-lift passengers
  lobbyBtn const & source;
  time_t when; //useful for priority setting
  bool completed; //can be completed by any lift L, even if not assigned to L
  
  Request(lobbyBtn const & s): source(s), when(time(0)), completed(false){}
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
  bool isDoorOpen; 
  
  /*Below two data structures are distinct*/
  set<Level> targets; //populated by passengers inside the lift 
  set<shared_ptr<Request>> assignedRequests; //assigned by system
  
  Lift(int _id): id(_id), dir(LiftDir::none), level(1){}
  void move(); /*based on direction+level+targets and nothing else
  Note some target could be in the opposite direction but since 
  we have taken it on we will service it  */
  
  void onDoorOpen(){
    if (isDoorOpen){
      // set current level..
	  
      this->targets.erase(this->level);
	  cleanupAssigned();
	}
  }
  void addTargets(); /*Any time passengers in lift can add targets. Only When lift 
  door opens, will system remove targets */
  
  void cleanupAssigned(){ /*This is the only place to remove a previoiusly assigned 
  requests to a lift.
  * When lift opens door at Level 3, assigned request from Level 3 is completed 
  and removed.
  * When this lift (X) is not at Level 3, and another lift (Y) happens to carry a 
  passenger to stop at Level 3 and complete the same request even though the request 
  is assigned to this Lift X. Such lucky events could happen in any iteration 
  of work(), so every iteration of work() needs to call cleanupAssigned().
  */
    for(auto it=this->assignedRequests.begin(); it!=assignedRequests.end();)
	  if ((*it)->completed || isDoorOpen && this->level==(*it)->source.level) 
	    assignedRequests.erase(it++);
	  else 
	    ++it;
  }
  bool shouldTakeOn(Request const & req) const; 
  /*based on current direction/level, decide to take the request or not. Optimization needed.
  Note if a request has been pending for a long time we will take it on unconditionally*/
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
	lift.addTargets();
    if(lift.targets.empty() && lift.assignedRequests.empty()) cout<<lift.id<<" has no target no assignment and will not move\n";
	else lift.move();
  }
}
int main(){
  int microseconds=1;
  for(;;){
    if (work() < 0) break;
	microseconds=calcDuration(); // based on Lift objects and the "unserviced"
	usleep(microseconds);
  }
  cout<<"requested to termination\n";
}
//Requirement https://bintanvictor.wordpress.com/2018/03/16/elevator-design/
