from math import sqrt
#smallFactors is sorted from low to high

def factorize(bigNum, smallFactors):
  '''find each formula to factorize bigNum, but when print it, also print smallFactors
  
  return true if our loop had any success
  '''
  print 'breaking up', bigNum, smallFactors
  #isGood=False
  tmp = smallFactors[-1] if smallFactors else 2 #highest existing factor
  for f in xrange(tmp, int(sqrt(bigNum))+1):
    if bigNum%f: continue
    print f, 'is a factor of', bigNum
    factorize(bigNum/f, smallFactors + (f,))
  #print 'returning with bigNum=', bigNum, 'f=',f   
  #return isGood

def main():
  factorize(36, tuple())
main()
'''Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
Based on https://github.com/tiger40490/repo1/blob/cpp1/cpp1/combo_permu/factorize_AQR.cpp

--for 36 we want
fac 36 () iterating from 2 to 6
  fac 18 (+2) iterating from 2 to 4
    fac 9 (2, +2)
      fac 3 (2,2, +3)
    fac 6 (2, +3)
  fac 12 (+3) iterating from 3 to 3
    fac 4 (3, +3)
  fac 9 (+4)    
  fac 6 (+6)
--for 12 we want
factorize 12 ()
 factorize 6 (+2)
  factorize 3 (2,+2)
 factorize 4 (+3)
'''