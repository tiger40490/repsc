#include <iostream>
using namespace std;
struct Component{
  char unused='x';
  Component(){cout<<"Component ctor\n"; }
};
struct MutableShip{
  int const id;//const primitive field needs ctor initializer
  Component const circle;
  MutableShip():id(0) { 
    //circle=Component{}; //illegal
    cout<<"MutableShip ctor using default-init on const field\n";
  }
  MutableShip(string unused):id(0), circle{Component{}} { 
    cout<<"MutableShip ctor with initializer\n";
  }
};

struct ImmutableShip{
  int const id;
  Component /*const*/ circle;
  ImmutableShip():id(0) /*circle{Component{}}*/ { 
    circle=Component{};
    cout<<"ImmutableShip initializing inside ctor \n";
  }  
  ImmutableShip(bool unused):id(0), circle{Component{}} { 
    //circle=Component{};
    cout<<"ImmutableShip ctor with initializer \n";
  }
};
int main(){
  MutableShip default_Init{};
  MutableShip use_Initializer{"use initializer for const field"};
  ImmutableShip initializeTwice{};
  ImmutableShip initializeOnce(true);
}/*goal: investigate the initialization of const fields
-- for class-type fields like const Component
default-initialization is implicit, so I don't need to write any explicit initialization.

If I use a ctor-initializer, then default-initialization won't happen !

In both cases, there's never a double-init on the const field.

Illegal to initialize it in ctor body

-- for class-type fields like non-const Component
If I initialize it in ctor body, then this is the 2nd initialization, after the default-initialization !

If I initialize it in ctor-initializer, then default-initialization is suppressed.
-- for primitive fields like const int
initialization via ctor-initializer is needed.
illegal to initialize it in ctor body
illegal to leave the field uninitialized
*/