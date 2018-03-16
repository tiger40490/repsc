#include <iostream>
#include <set> //or unordered_set
#include <deque>
using namespace std;
using Level = unsigned short; //same as typedef

enum class Dir {u, d, none};

struct ButtonUD{ //button in lift lobby
  Level const level;
  Dir direction;
  
  ButtonUD(Level l, Dir dir): level(l), direction(dir){}
};
vector<ButtponUD> const all_buttons={ButtonUD(1, Dir.u),
ButtonUD(2, Dir.u),ButtonUD(2, Dir.d),
ButtonUD(3, Dir.u),ButtonUD(3, Dir.d),
ButtonUD(4, Dir.u),ButtonUD(4, Dir.d),
ButtonUD(5, Dir.u),ButtonUD(5, Dir.d),
ButtonUD(6, Dir.u),ButtonUD(6, Dir.d),
ButtonUD(7, Dir.d)};

struct Request{
  ButtonUD const & source;
  time_t when; //used to adjust priority
  
  Request(ButtonUD const & s): source(s), when(time(0)){}
};
struct Lift{
  int id;
  Dir dir;
  Level level;
  size_t passengerCnt;
  set<Level> targets; //populated by passengers inside the lift or by setTarget()
  
  Lift(int i): id(i), dir(Dir.none), level(1){}
} lift1(1);