// v0.8
//
#include "ValueObj.h"
#include <memory>
using namespace std;

const char ICE = '.'; //not needed in visualization

static //this function should not be used outside this file
shared_ptr<Square> mkSq(int x, int y, bool isBottom=true){
	return make_shared<Square>(x,y,isBottom); 
}

Shape 
I('I', *mkSq(0,0), *mkSq(1,0), *mkSq(2,0), *mkSq(3,0)),
Q('Q', *mkSq(0,0), *mkSq(1,0), *mkSq(0,1,false), *mkSq(1,1,false)),

//S and Z are mirror images:
S('S', *mkSq(0,0), *mkSq(1,0), *mkSq(1,1,false), *mkSq(2,1)),
Z('Z', *mkSq(0,1), *mkSq(1,0), *mkSq(2,0), *mkSq(1,1,false)),

//L and Z are mirror images:
L('L', *mkSq(0,0), *mkSq(1,0), *mkSq(0,1,false), *mkSq(0,2,false)),
J('J', *mkSq(0,0), *mkSq(1,0), *mkSq(1,1,false), *mkSq(1,2,false)),

T('T', *mkSq(2,1), *mkSq(1,1,false), *mkSq(1,0), *mkSq(0,1));

