'''todo: clean up
todo: load test

Not sure why the new solution is much slower than CSY
'''
from math import sqrt
from datetime import datetime
import bisect, os, sys
import generic_factorize
cnt=0; recursionLevel=0
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)
isVerbose=True
recurCnt=dict([['CSY',0], ['prime',0]])

def getSmallDivisors(bigNum):
  divisors, _ = generic_factorize.get_divisors(bigNum)
  return divisors[ : bisect.bisect_right(divisors, sqrt(bigNum))]
      
def recurs(bigNum, divisors, lowerFactors=tuple()):
  global cnt, recursionLevel
  recurCnt['prime']+=1
  assert sorted(lowerFactors) == list(lowerFactors), 'should be sorted low to high'
  assert len( lowerFactors ) == recursionLevel
  recursionLevel += 1
  if lowerFactors: # i.e. non-empty
    cnt+=1
    if isVerbose: print '. '*(recursionLevel-2) + str(list(lowerFactors)), bigNum
  else: 
    print '------- factorizing', bigNum
    cnt=0
    
  for i in xrange(len(divisors)): # scan all divisors from _start to sqrt of current bigNum
    f = divisors[i]
    if bigNum % f: continue
    new=bigNum/f
    if new < f: break
    
    recurs(new, divisors[i:], lowerFactors+(f,))
  recursionLevel -= 1
def recursCSY(remain, lowerFactors=tuple()):
  '''job: find each formula to factorize remain, but when print it, also print lowerFactors
  '''
  global cnt, recursionLevel
  recurCnt['CSY']+=1
  assert sorted(lowerFactors) == list(lowerFactors), 'should be sorted low to high'
  assert len( lowerFactors ) == recursionLevel
  recursionLevel += 1
  if lowerFactors: # i.e. non-empty
    assert lowerFactors[-1] <= remain, 'last lowerFactors item should not exceed remain'
    cnt+=1
    _start = lowerFactors[-1] # highest existing factor -- #1 trick in this algorithm
    if isVerbose: print '. '*(recursionLevel-2) + str(lowerFactors), remain
  else: 
    print '------- CSY factorizing', remain
    cnt=0
    _start = 2 # smallest factor in the universe
    
  # loop below is too ineffient. Should replace the xrange with the remaining "factors"
  for f in xrange(_start, int(sqrt(remain))+1):
    if remain%f: continue
    recursCSY(remain/f, lowerFactors+(f,))
  recursionLevel -= 1
def factorize(bigNum):
  global isVerbose;  isVerbose = False
  if bigNum < 9999:
    isVerbose=True
    
  startTime=datetime.now()
  recursCSY(bigNum)
  print (datetime.now()-startTime).total_seconds(), 'seconds'
    
  startTime=datetime.now()
  recurs(bigNum, getSmallDivisors(bigNum))
  print (datetime.now()-startTime).total_seconds(), 'seconds'
def main():
  #print get_divisors(600)
  factorize(60); assert(10 == cnt)
  #return
  factorize(36); assert(8  == cnt)
  factorize(24); assert(6  == cnt)
  factorize(12); assert(3  == cnt)
  
  A=2; B=3; C=5; D=7
  #factorize((A*C)**9) #
  factorize(A**7 * B**4 * C**3 * D**2) # need to use q(python -u)
  print recurCnt
  return
main()
'''Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
--for 36 we want
fac 36 () iterating from 2 to 6
  fac 18 (+2) iterating from 2 to 4
    fac 9 (2, +2)
      fac 3 (2,2, +3)
    fac 6 (2, +3)
  fac 12 (+3) iterating from 3 to 3
    fac 4 (3, +3)
  fac 9 (+4) # when factorizing 9, we ignore factors below 4, since they are taken care of in an earlier recursive call
  fac 6 (+6)
'''
