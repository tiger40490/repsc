import sys, os, random; from pprint import pprint
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0) # worked
li=range(9); random.shuffle(li); pprint(li)
## list methods:
print li.pop(), li 
li.insert(0,-55) #insert at 0th position
li.remove(-55) #remove an item equal to 55, assuming it exists
del li[0] #; print li # remove by index
## dict init:
pprint({1:'j', 3+2:'a'}); sys.exit()

'''This is a template for timed online tests. It saves screen real estate
'''