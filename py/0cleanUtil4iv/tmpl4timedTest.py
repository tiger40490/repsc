import sys, os, random; from pprint import pprint
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0) # worked
li=range(9); random.shuffle(li); pprint(li)
## list methods + operators:
print li.pop(), '  ', li
li.insert(0,-55); print li #insert at 0th position
li.remove(-55) #remove an item equal to -55, assuming it exists
del li[0] ; print 'del[0]:',li # remove by index
print 'sum =',sum(li)
del li[:]; print li #wipe clean in-place
## dict init:
di={1:'j', 3+2:'a'}; 
for k,v in di.items(): print v,k
print di.keys(); sys.exit()

'''This is a template for timed online tests. It saves screen real estate
'''