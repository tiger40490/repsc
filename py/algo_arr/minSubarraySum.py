'''
showcase: sum(iterable)
'''
def solve(arr):
  '''my test and coding will focus on the first return value. The other return values are trivial, low mkt-value and supported as best-effort
  '''
  ret = [0,None, None] # [ minSum, le, ri ] of the best subarray 
  b4le = -1
  meh = 0 #min subarray sum ending here, possibly empty array
  for i, v in enumerate(arr):
    print i,":",v
    if meh + v > 0: 
      meh = 0; b4le=i; continue
    meh += v
    if meh < ret[0]: ret = [meh, b4le+1, i]
  print 'returning', ret
  if ret[1] is not None:
    assert ret[1] <= ret[2]
    assert ret[0] == sum(arr[ret[1] : ret[2]+1]) 
  return ret

assert( [-16, 13,16] == solve([1,3,-6,-2,0,-7,14,7,-5,12,-8,11,5,-9,-2,3,-8]) )
assert( [-11, 5,7] == solve([1,-3,-6,7,4,-5,2,-8,5,9,-1,3,8]) )
assert( [-10, 0,2] == solve([-3,-6,-1]) ) # all negative ints
assert( [0, None,None] == solve([1,3,6,7,4,5,2,8,5,9,1,3,8]) ) # all positive ints
assert( [0, None,None] == solve([0]) ) 
assert( [0, None,None] == solve([44]) ) 

'''Req: given a signed int array, find the subarray with minimum sum. If all elements are positive, then return 0.

Kadane algo is directly applicable. This is a rewrite/drill of the algo.
'''