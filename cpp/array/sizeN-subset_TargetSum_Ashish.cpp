#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//by CSY
void fun(vector<int> arr, int sum, int count, vector<int> v){
  if (sum <= 0 || count < 1 || arr.size() < count)
    return;

  if (count == 1){
    vector<int>::iterator it;
    it = find(arr.begin(), arr.end(), sum);
    if (it != arr.end()){
      for (int i=0; i<v.size(); i++)
        cout << v[i] << " "; 
      cout << sum << endl;
    }
    return;
  }
  v.push_back(arr.front());
  vector<int> arr2(arr.begin()+1, arr.end());
  fun(arr2, sum-arr.front(), count-1, v);
  v.pop_back();
  if (arr2.size() >= count)
    fun(arr2, sum, count, v);
}

int main(){
    int NUMBER=9, SUM=18, COUNT=4;
    vector<int> arr, v;
    for (int j=1; j<=NUMBER; j++) arr.push_back(j);
    cout <<"\nnumber of card=" << NUMBER << ", SUM=" << SUM << ", COUNT=" << COUNT << endl;
    fun(arr, SUM, COUNT, v);
}
//Req: https://bintanvictor.wordpress.com/2015/11/22/algo-problem-ashish-array-sum/