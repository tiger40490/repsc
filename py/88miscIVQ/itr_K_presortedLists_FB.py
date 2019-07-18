from heapq import *
class Item:
  def __init__(self, payload, whichList):
    self.v = payload
    self.lid = whichList
    #self.idx .. not needed, due to ii
a = [[1,2,5,7],[1,2,3,5],[2,4,6,8],[3,5,7]]
k=len(a)
ii = [0] * k # k internal iterators
heap = []
def next():
  ret = heappop(heap)
  lid = ret.lid
  picked = a[lid]
  if ii[lid] < len(picked) - 1:
     ii[lid] += 1
     heappush(heap, Item(picked[ii[lid]], lid) )
     # note if ii[55] is already at the last item of a[55], then this list will not get picked up again
  return ret.v
def init():
  for i in xrange(k):
    heap.append ( Item(a[i][0], i) )
  heapify(heap)
def hasNext():
  return len(heap)>0
'''Requirement: given K pre-sorted immutable lists, each up to N items, return an iterator that yields all (up to K*N) items sorted sequence

I first proposed pair-wise merge. Since there are logK passes,
Time complexity = O(NK logK)
Very first pass i must create a single list up to NK items. then I can reuse this list in each merge. so
space complexity = NK, but I said NK*logK

Then interviewer Richard suggested iterating over the K lists so I implemented the solution here.
Space complexity = K
Time complexity:
next() O(logK) due to popping
init() O(K)
hasNext() O(1)

'''