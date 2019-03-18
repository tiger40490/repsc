import sys, os, random; from pprint import pprint

''' simple utility for timed coding tests.
random.shuffle() is easier to remember than random.sample() !
'''
def randomGen(cnt, minOutputVal, min=0):
  assert cnt <= minOutputVal-min+1 #optional input validation
  ret=range(min, minOutputVal+1, 1);
  random.shuffle(ret); return ret[:cnt]
  
pprint(randomGen(5,9))
pprint(randomGen(5,4))
