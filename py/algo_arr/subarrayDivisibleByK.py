'''Another int-array problem, involving some math

todo: try the solution in leetcode #974 and #560

'''
import sys, inspect
from collections import defaultdict
def kSub(k, nums):
 print nums
 ret =  kSub2(k, nums)
 assert kSubBruteForce(k, nums) == ret
 return ret 
def kSubBruteForce(k, nums):
 '''My solution below passed 6 tests and timed out on some tests without giving wrong answers.

 I won't spend much time as this problem is not a practical or popular.

 1st challenge was ECT speed. I was able to pass one test case in 5-10 minutes, struggling against syntax (thank God I didn't choose c++)

 2nd challenge is algorithm efficiency. 95% of the time this doesn't matter so much meaning interviewer doesn't care at all. This one is an exception.
 '''
 a=nums; sz=len(nums); ranges=0; ret=0
 for le in xrange(sz):
   sum=0
   for ri in xrange(le,sz):
     sum=(sum+a[ri])%k
     if sum==0: ret+=1 #; print ':)'
     # print le,ri, '>>', sum, '<<', a[le:ri+1]
     ranges+=1
 assert ranges == sz*(sz+1)/2  
 print inspect.stack()[0][3], "returning", ret
 return ret
def kSub2(k, nums):
  ''' Linear time solution, based on Leetcode discussion 
  '''
  cumsum=0; cnt=0;  
  frq=defaultdict(list) #list of positions
  frq[0].append(-1)
  for i in xrange(len(nums)): 
    a = nums[i]
    cumsum = (cumsum+a)%k
    club = frq[cumsum]
    print a, club
    for pos in club:
      tmp = sum(nums[pos+1:i+1])
      print 'checking', pos, i, tmp
      assert tmp%k == 0
    cnt += len(club)
    club.append(i)
  print frq
  return cnt
assert 10==kSub(5, [5,10,11,9,5])
#sys.exit()
assert 4 ==kSub(3, [1,2,3,4,1])
assert 5 ==kSub(4, [2,3,5,6,7,4,3])
assert 6 ==kSub(15, [45, 15, 7, 8, 10])
'''2019 Hackerrank problem: given a natural number array nums and a divisor k, find all subarrays whose sum is divisible by k
'''