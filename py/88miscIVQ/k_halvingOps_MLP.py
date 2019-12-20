'''
showcase max_item_pos(list)
showcase max heap using neg ints

todo: reduce code dup on heappop
'''
import math
import heapq
arr=list()

def brute(k):
  mutable = arr[:]
  for i in xrange(k):
    #print mutable
    idx = max(xrange(len(mutable)), key=lambda x: mutable[x])
    mutable[idx] = math.ceil(mutable[idx]/2.0)
  ret = int(sum(mutable))
  print ret, 'returned from brute()'
  return ret
    
def solve(k, aa):
  global arr; arr=aa
  assert min(arr) > 0
  # build max heap
  heap=aa[0:k]
  heapq.heapify(heap)
  print 'min-heap is', heap
  for v in aa[k:] :
    if heap[0] >= v: continue
    heapq.heapreplace(heap,v)
  for i in xrange(len(heap)): heap[i] *= -1
  heapq.heapify(heap)
  ret = sum(aa)
  print ret, '=initial sum; max heap=', heap
  cuts = 0
  fat = -heapq.heappop(heap)
  while True:
    assert len(heap) == k-1
    top = -heap[0]
    half = int(math.ceil(fat/2.0)); assert half > 0
    ret -= fat - half; assert ret > 0
    print ret, 'is the updated sum'
    cuts += 1; 
    if cuts == k: return ret
    fat = half
    if fat < top: 
      heapq.heappush(heap, -fat)
      fat = -heapq.heappop(heap)
  
def test():
  global k
  k=5
  assert solve(k, [39,11,19,62,4,31,22,52,2,4,15,13]) == brute(k)
  assert solve(k, [11,9,6,7,4,3,2,5,12,4,15,13]) == brute(k)
  assert solve(k, [1,3,9,16,4,31,12,5,2,4,5,3]) == brute(k)
if __name__ == "__main__":
  test()
'''Req: given a collection of N positive integers, you perform K operations like "half the biggest element and replace it with its own ceiling". Find the collection sum afterwards.
https://bintanvictor.wordpress.com/wp-admin/post.php?post=35955&action=edit

k_halvingOp.py

'''