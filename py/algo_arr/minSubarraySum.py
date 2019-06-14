def solve(arr): # return subarray sum
  meh = 0 #min subarray sum ending here, possibly empty array
  for i, v in enumerate(arr):
    print i,":",v
    
solve([1,-3,-6,7,4,-5,2,-8,5,9,-1,3,8])
#solve([1,3,6,7,4,5,2,8,5,9,1,3,8])
'''Req: given a signed int array, find the non-empty subarray with minimum sum. 
If all elements are positive, then return a singular array.
'''