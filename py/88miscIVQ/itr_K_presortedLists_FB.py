'''
showcase: how to put an artificial loop around a yield-block. Loop termination is by return|break
showcase: yield function with an explicit init

My [[python cookbook]] P721 has another solution, less readable
'''
from heapq import *
a = [[1,3,5,7],[0],[2,3,5],[0,2,4,6,8],[17]]
k=len(a)
ii = [0] * k # k internal iterators, maintained in static memory. In my on-site interview, I replaced this with a 3rd field of the heap payload, but with higher DAM overhead IMO. 
heap = []
cnt=0
def next():
 init()
 
 #while len(heap): # cleaner implementation
 while True: #yield needs a loop, even if artificial
  if len(heap) == 0: return # return/break both usable, if in a while-true loop
  ret = heappop(heap)
  lid = ret[1]
  picked = a[lid]
  if ii[lid] < len(picked) - 1:
    ii[lid] += 1
    heappush(heap, (picked[ii[lid]], lid) )
    # note if ii[55] is already at the last item of a[55], then this list will not get picked up again
  yield ret[0]
def init():
  global cnt
  for w in xrange(k): # w=whichList
    heap.append ( (a[w][0], w) )
    cnt += len(a[w])
  heapify(heap)
def test():
  output = [ i for i in next() ]
  print output
  assert output == sorted(output)
  assert len(output) == cnt
test()
'''Requirement: https://bintanvictor.wordpress.com/wp-admin/post.php?post=31626&action=edit

Q: given K pre-sorted immutable lists, each up to N items, return an iterator that on demand yields each of the (up to K*N) items in sorted sequence.
'''