#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//by my friend CSY
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
    int TOTAL_CNT=9, SUM=18, REQ_CNT=4;
    vector<int> arr, v;
    for (int j=1; j<=TOTAL_CNT; j++) arr.push_back(j);
    cout <<"\n number of card=" << TOTAL_CNT << ", SUM=" << SUM << ", REQ_CNT=" << REQ_CNT << endl;
    fun(arr, SUM, REQ_CNT, v);
}
//Req: https://bintanvictor.wordpress.com/2015/11/22/algo-problem-ashish-array-sum/
