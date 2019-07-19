'''
todo: add asserts
'''
from heapq import *
'''
class Item:
  def __init__(self, payload, whichList):
    self.v = payload
    self.lid = whichList
    #self.idx .. not needed, due to ii
'''
a = [[1,3,5,7],[0],[2,3,5],[0,2,4,6,8],[17]]
k=len(a)
ii = [0] * k # k internal iterators
heap = []
cnt=0
def next():
 while True: #needed by yield
  if len(heap) == 0: return
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
def hasNext():
  return len(heap)>0
def test():
  init()  
  output = [ i for i in next() ]
  print output
  assert output == sorted(output)
  assert len(output) == cnt
test()
'''Requirement: https://bintanvictor.wordpress.com/wp-admin/post.php?post=31626&action=edit

Q: given K pre-sorted immutable lists, each up to N items, return an iterator that on demand yields each of the (up to K*N) items in sorted sequence.
'''