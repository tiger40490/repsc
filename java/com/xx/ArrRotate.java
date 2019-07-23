public class Solution {
  public void rotate(int[] nums, int k) {
    k = k % nums.length;
    int count = 0;
    for (int start = 0; count < nums.length; start++) {
      int curPos = start;
      int preVal = nums[start];
      do {
        int evictPos = (curPos + k) % nums.length;
        int evictVal = nums[evictPos]; //use evictPos after update
        nums[evictPos] = preVal; //use preVal before update 
        
        preVal = evictVal;
        curPos = evictPos;
        count++;
      } while (start != curPos);
    }//for
  }//method
}// Based on https://leetcode.com/problems/rotate-array/solution/