import sys, os, random; from pprint import pprint
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0) # worked
li=range(9); random.shuffle(li); pprint(li)
## list methods + operators:
print li.pop(), '  ', li
li.insert(0,-55); print li #insert at 0th position
li.remove(-55) #remove an item equal to -55, assuming it exists
del li[0] ; print 'del[0]:',li # remove by index
print 'sum =', sum(li)
del li[:]; print li #wipe clean in-place
## dict init:
di=dict(red=1, blue=2) # no quoting required
for k,v in di.items(): print k,v
di={1:'j', 3+2:'a'}; # supports computed key
for k,v in di.items(): print k,v
print di.keys(), di.values()

print 'vvvvvvvvvvvvvvvvv defaultdict'
from collections import defaultdict as ddict
di=ddict(lambda: [[2,3],[5,4]])
print di['invalidKey']

di=ddict(lambda: 0) # similar to defaultdict(int)?
print 23 in di
print di[23]

## matrix
width,height=3,2
m = [['_' for x in range(width)] for y in range(height)]
pprint(m); sys.exit()
'''This is a template for timed online tests. It saves screen real estate
'''