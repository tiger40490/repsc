def solve(arr):
  ret = [0,None, None] # [ minSum, le, ri ] 
  b4le=None
  meh = 0 #min subarray sum ending here, possibly empty array
  for i, v in enumerate(arr):
    print i,":",v
    if meh + v > 0: 
      meh = 0; b4le=i; continue
    meh += v
    if meh < ret[0]: ret = [meh, b4le+1, i]
  print 'returning', ret
  assert ret[1] <= ret[2] #???
  assert ret[0] == sum(arr[ret[1]:ret[2]+1]) 
  return ret
assert( [-11, 5,7] == solve([1,-3,-6,7,4,-5,2,-8,5,9,-1,3,8]) )
#solve([1,3,6,7,4,5,2,8,5,9,1,3,8])
'''Req: given a signed int array, find the non-empty subarray with minimum sum. 
If all elements are positive, then return a singular array.
'''