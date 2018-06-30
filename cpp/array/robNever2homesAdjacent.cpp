//accepted at Leetcode. Not very efficient, but relatively simple
#include <vector>
#include <iostream>
using namespace std;

int rob(vector<int>& nums) {
        int bn = 0, //best plan up to current house
          bp=0, //best up to prev
          bpp=0; // bestUpToPrevPrev
        for (int i=0; i<nums.size(); ++i){
            int tmp = bpp;
            bpp = bp;
            bp = bn;
            bn = nums[i] + max(tmp, bpp);
        }
        return max(bn, bp);        
}
int main(){
  cout<< rob({2,1,1,2});
}/* Req: https://leetcode.com/problems/house-robber/description/

You are a robber planning to rob houses along a street. Each house has a certain 
amount of money stashed, the only constraint stopping you from robbing each of them
is that adjacent houses have security system connected and it will automatically 
contact the police if two adjacent houses were broken into.
*/
