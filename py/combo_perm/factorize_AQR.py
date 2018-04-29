from math import sqrt
#existingFactors=list() # sorted from low to high

def factorize(bigNum, existingFactors):
  '''find each formula to factorize bigNum, but when print it, also print existingFactors
  
  return true if our loop had any success
  '''
  print 'breaking up', bigNum, existingFactors
  isGood=False
  f = existingFactors[0] if existingFactors else 2
  while f<=sqrt(bigNum):
    if bigNum%f: f+=1; continue
    print f, 'is a factor of', bigNum
    isGood=True
    if not factorize(bigNum/f, existingFactors + (f,)):
      f +=1
  #print 'returning with bigNum=', bigNum, 'f=',f   
  return isGood

def main():
  factorize(24, tuple())
main()
'''Requirement: https://bintanvictor.wordpress.com/2017/04/16/factorize-a-natural-number-aqr/
Based on https://github.com/tiger40490/repo1/blob/cpp1/cpp1/combo_permu/factorize_AQR.cpp
'''