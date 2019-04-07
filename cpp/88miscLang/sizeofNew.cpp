#include <iostream>
#define M2(T) MeasureNew<T>(#T)
using namespace std;
template<typename T> void MeasureNew(string text){
  cout<<text<<" "<<sizeof(T)<<"  ";
  char* lastp = nullptr;
  for (int i=0; i<11; ++i){
    T* p=new T;
    auto thisp = reinterpret_cast<char*>(p);
    if (lastp != 0) cout<<" " <<thisp-lastp;
    lastp = thisp;
  } cout<< endl;
}
struct i1{int i; };
struct ic{int i; char c; };
struct c1{char c; };
struct ci{char c; int i; };
int main(){
  //M2(c1);
  //M2(i1);
  M2(ci);
  M2(ic);
}/*Goal: measure total memory usage by each new() allocation
based on P186 [[Programming Pearls]]. 

Note: first call to MeasureNew() in main() gives best i.e. most consistent result. If you call MeasureNew(ic) after other MeasureNew(...) calls, then result is hard to interpret. I guess this is the behavior of the new() allocator.

Note: Macro below worked better than template at the time of the book.

#define MeasureNewOriginal(T, text) { \
  cout<<text<<" "<<sizeof(T)<<"  "; \
  char* lastp = 0; \
  for (int i=0; i<11; ++i){ \
    T* p=new T; \
    auto thisp = reinterpret_cast<char*>(p); \
    if (lastp != 0) cout<<" " <<thisp-lastp; \
    lastp = thisp; \
  } cout<< endl; \
}
*/
