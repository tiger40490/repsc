'''Another int-array problem, involving some math

todo: try the solution in leetcode #974 and #560

My solution below passed 6 tests and timed out on some tests without giving wrong answers.

I won't spend much time as this problem is not a practical or popular.

1st challenge was ECT speed. I was able to pass one test case in 5-10 minutes, struggling against syntax (thank God I didn't choose c++)

2nd challenge is algorithm efficiency. 95% of the time this doesn't matter so much meaning interviewer doesn't care at all. This one is an exception.
'''
import sys
def kSub(k, nums):
 print nums
 a=nums; sz=len(nums); ranges=0; ret=0
 for le in xrange(sz):
   sum=0
   for ri in xrange(le,sz):
     sum=(sum+a[ri])%k
     if sum==0: ret+=1 #; print ':)'
     print le,ri, '>>', sum, '<<', a[le:ri+1]
     ranges+=1
 assert ranges == sz*(sz+1)/2  
 print "returning", ret
 return ret
assert 10==kSub(5, [5,10,11,9,5])
#sys.exit()
assert 4 ==kSub(3, [1,2,3,4,1])
assert 5 ==kSub(4, [2,3,5,6,7,4,3])
assert 6 ==kSub(15, [45, 15, 7, 8, 10])
'''2019 Hackerrank problem: given a natural number array nums and a divisor k, find all subarrays whose sum is divisible by k
'''