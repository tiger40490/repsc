from math import sqrt
cnt=0; recursionLevel=0
def recursCSY(tgt, smallFactors=tuple()):
  '''find each formula to factorize tgt, but when print it, also print smallFactors
  '''
  global cnt, recursionLevel
  assert sorted(smallFactors) == list(smallFactors), 'should be sorted low to high'
  assert len( smallFactors ) == recursionLevel
  recursionLevel += 1
  if smallFactors: # i.e. non-empty
    assert smallFactors[-1] <= tgt
    cnt+=1
    _start = smallFactors[-1] # highest existing factor -- smartest trick in this algorithm
    #print smallFactors, tgt
  else: 
    cnt=0
    _start = 2
    print '------- factorizing', tgt
  for f in xrange(_start, int(sqrt(tgt))+1):
    if tgt%f: continue
    recursCSY(tgt/f, smallFactors+(f,))
  recursionLevel -= 1
  return cnt
def factorize(tgt):
  return recursCSY(tgt)
def main():
  assert(8  == factorize(36));
  #return
  assert(10 == factorize(60));
  assert(6  == factorize(24));
  assert(3  == factorize(12));  
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
