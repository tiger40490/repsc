//compile with g++ -c this.file
//showcase: type alias, same as typedef
//showcase: enum class
#include <iostream>
#include <time.h>
#include <unistd.h>
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
  
  Request(Btn const & s): source(s), when(time(0)){}
  bool operator<(Request const & other) const{
  //not used for priority, but to remove duplicate requests
    if (this->source.direction != other.source.direction)
      return this->source.direction < other.source.direction;
	else
  	  return this->source.level < other.source.level; 
  }
};
struct Lift{
  int id;
  LiftDir dir;
  Level level;
  size_t passengerCnt;
  set<Level> targets; //populated by passengers inside the lift or by setTarget()
  
  Lift(int _id): id(_id), dir(LiftDir::none), level(1){}
  void move(); //based on direction+level+targets and nothing else
  void addPessengerRequests(); //passengers can push buttons inside the lift to add "targets"
  bool canTakeOn(Request const & req) const; //based on current direction/level, see if we can take on a request
};
vector<Lift> lifts={Lift(1), Lift(2)};
set<Request> unserviced; //whenwe take on a request, it's removed from here

int calcDuration();
bool isTerminationNeeded();
void receiveNewRequests(); //add new requests to unserviced and do nothing else

void addTargetsToLifts(){
  size_t taken=0;
  for(auto req = unserviced.begin(); req!=unserviced.end(); ++req){
    bool isTakenOn = false;
    for(auto & lift: lifts){
	   if (lift.canTakeOn(*req)){
	     unserviced.erase(req);
		 lift.targets.insert(req->source.level);
		 isTakenOn = true;
		 ++taken;
	     break;
	   }
	}
	if (!isTakenOn) cout<<req->source.level<<" is unserviceable at the moment\n";
  }
  cout<<taken<<" requests taken up... Now process request by in-lift passengers...\n";
  for(auto & lift: lifts) lift.addPessengerRequests();
}
int work(){
  if (isTerminationNeeded()) return -1;
  receiveNewRequests(); 
  addTargetsToLifts();
  for(auto & lift: lifts){
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