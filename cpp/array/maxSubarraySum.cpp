// showcasing macro for long var name
//
#include<iostream>
#include<vector>
#include<climits>
#define ss if(1>0) cout
#define meh max_ending_here
using namespace std;

vector<int> vec = {-2, -3, -4, -1, -2, -1, -5, -3};
int main(){
        int ret = INT_MIN, meh = 0;

        for (int i = 0; i < vec.size(); ++i) {
                meh = meh + vec[i];
                if (ret < meh) ret = meh; //obvious
                if (meh < 0) meh = 0;
                ss<<meh<<" = meh; ret = "<<ret<<endl;
        }
        cout << "Maximum contiguous sum is " << ret;
}
/* Requirement: print largest contiguous array sum, based on
 * https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
 */
