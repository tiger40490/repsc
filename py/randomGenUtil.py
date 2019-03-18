import sys, os, random; from pprint import pprint

''' simple utility for timed coding tests.

random.shuffle() is easier to remember than random.sample() !
random.shuffle() can handle dupe items, as demonstrated in "extend" line
'''
def randomGen(cnt, minOutputVal, min=0):
  assert cnt <= minOutputVal-min+1 #optional input validation
  ret=range(min, minOutputVal+1, 1);
  # ret.extend(ret); print ret #add the same items
  random.shuffle(ret); return ret[:cnt]
  
print randomGen(5,9)
print randomGen(5,4)
