#include <iostream>
#define MeasureNew(T, text) { \
  cout<<text<<" "<<sizeof(T)<<"  "; \
  char* lastp = 0; \
  for (int i=0; i<11; ++i){ \
    T* p=new T; \
    auto thisp = reinterpret_cast<char*>(p); \
    if (lastp != 0) cout<<" " <<thisp-lastp; \
    lastp = thisp; \
  } cout<< endl; \
}
using namespace std;
struct c1 {char c; };
struct i1 {int i; };
struct ic{int i; char c; };
struct ci{char c; int i; };
int main(){
  MeasureNew(c1, "c1");
  MeasureNew(i1, "i1");
  MeasureNew(ci, "ci");
  MeasureNew(ic, "ic");
}/*Goal: measure total memory usage by each new() allocation
based on P186 [[Programming Pearls]]. 

Note: first call to MeasureNew() in main() gives best i.e. most consistent result. If you call MeasureNew(ic) after other MeasureNew(...) calls, then result is hard to interpret. I guess this is the behavior of the new() allocator.

Note: Macro worked better than template at the time of writing.
*/
