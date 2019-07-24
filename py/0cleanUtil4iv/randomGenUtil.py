import sys, os, random; from pprint import pprint

''' simple utility for timed coding tests.

random.shuffle() is easier to remember than random.sample() ! Some complexities are handled by range()
random.shuffle() can handle dupe items, as demonstrated in "extend" line

Function returns distinct items if cnt is not too high. 
'''
def randomGen(cnt, maxOutputVal, min=1):
  ret=range(min, maxOutputVal+1, 1);
  for i in xrange(cnt/(maxOutputVal-min+1)):
    ret.extend(ret); 
  #print len(ret), 'items in pool:', ret
  ret = ret[:cnt]; random.shuffle(ret); return ret
  
print randomGen(9,9)
print randomGen(5,4)
