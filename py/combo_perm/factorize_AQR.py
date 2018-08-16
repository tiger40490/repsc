from math import sqrt
cnt=0; recursionLevel=0
def recursCSY(remain, lowerFactors=tuple()):
  '''job: find each formula to factorize remain, but when print it, also print lowerFactors
  '''
  global cnt, recursionLevel
  assert sorted(lowerFactors) == list(lowerFactors), 'should be sorted low to high'
  assert len( lowerFactors ) == recursionLevel
  recursionLevel += 1
  if lowerFactors: # i.e. non-empty
    assert lowerFactors[-1] <= remain, 'last lowerFactors item should not exceed remain'
    cnt+=1
    _start = lowerFactors[-1] # highest existing factor -- #1 trick in this algorithm
    print '. '*(recursionLevel-2) + str(lowerFactors), remain
  else: 
    print '------- factorizing', remain
    cnt=0
    _start = 2 # smallest factor in the universe
    
  # loop below is too ineffient. Should use the "non-distinct prime factors" described in blog
  for f in xrange(_start, int(sqrt(remain))+1):
    if remain%f: continue
    recursCSY(remain/f, lowerFactors+(f,))
  recursionLevel -= 1
def factorize(remain):
  recursCSY(remain)
def main():
  factorize(36); assert(8  == cnt)
  factorize(60); assert(10 == cnt)
  factorize(24); assert(6  == cnt)
  factorize(12); assert(3  == cnt)
  return
  A=2; B=3; C=5; D=7
  factorize((A*C)**12) # a trillion
  factorize(A**10 * B**8 * C**6 * D**4) # need to use q(python -u)
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
