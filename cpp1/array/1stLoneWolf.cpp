/* showcase saving itr values in container
 * showcase scoped enum
 * showcase cout macro
 */
#include <list>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>
#define ss if(2>1) cout
using namespace std;

typedef int Num;
vector<Num> arr={1,2,3,4,5, 1,1,2,3,4,5,6};
list<Num> greens;
enum class Color {Green, Brown};
typedef list<Num>::iterator Itr;
struct Status{
  Color color;
  Status(Itr i):_itr(i), color(Color::Green){}
  Itr itr(){
    assert(color == Color::Green); //Color:: is required for c++11 scoped enum
    return _itr;
  }
//  Status()...//no-arg ctor needed if we use op[]
private:
  Itr _itr;
};

unordered_map<Num, Status> lookup;

void firstLoneWolf(){
  for(int i=0; i<arr.size(); ++i){
    Num num = arr[i];
    ss<<num;
    if (lookup.count(num) == 0){
      ss<<" is a yet-unseen number\n";
      Itr whereInGreens = greens.insert(greens.end(), num);
      //ss<<*whereInGreens<<" <- whereInGreens\n";
      lookup.insert(make_pair(num, Status(whereInGreens)));
      //ss<<lookup.size()<<" = lookup.size()\n";
      continue;
    }
    auto & status (lookup.find(num)->second);
    if (status.color == Color::Brown) {
      ss<<" was already brown\n";
      continue;
    }
    ss<<" is turning Brown!\n";
    auto where = status.itr();
    //ss<<*where<<" <- where\n";
    greens.erase(where); //ss<<greens.size()<<" = greens.size()\n";
    status.color = Color::Brown;
  }
  cout<<greens.size()<<" = greens.size()\n";
  if (greens.size())
    cout<<*(greens.begin())<<" is the 1st lone wolf\n";
  else
    cout<<"no lone wolf left\n";
}
int main(){
  firstLoneWolf();
}
/*Requirmenet: if an integer appears only once in an array, then it’s a
 * lone wolf. Find the first lone wolf in a given array.
 *
 * https://wp.me/p74oew-CP is my blog post
 */
