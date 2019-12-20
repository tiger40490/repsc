'''
showcase max_item_pos(list)
showcase max heap using neg ints

Even though heapreplace() and heappushpop() are more efficient, I can't use them in this solution.
'''
import math, heapq
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
    
def lowTouchSolution(k, aa): # minimize pop/push on the heap since pop() is expensive at O(log k)
  global arr; arr=aa
  assert min(arr) > 0
  
  ## O(N logK) build max heap
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
  
  ## O(K logK) now use the heap only, and discard the rest of the collection
  cuts = 0
  while True:
    if len(heap) == k: 
      fat = -heapq.heappop(heap)
    half = int(math.ceil(fat/2.0)); assert half > 0
    ret -= fat - half; assert ret > 0
    print ret, 'is the updated sum, after cutting up', fat
    cuts += 1; 
    if cuts == k: return ret
    fat = half
    if fat < -heap[0]: # cutting too much into the fat
      heapq.heappush(heap, -fat)
  
def test():
  global k
  k=9
  assert lowTouchSolution(k, [249,11,1,512,4,1,2,4,5,1]) == brute(k)
  k=5
  assert lowTouchSolution(k, [39,11,19,962,4,31,22,52,2,4,15,13]) == brute(k)
  assert lowTouchSolution(k, [11,9,6,7,4,3,2,5,12,4,15,13]) == brute(k)
  assert lowTouchSolution(k, [1,3,9,16,4,31,12,5,2,4,5,3]) == brute(k)
if __name__ == "__main__":
  test()
'''Req: given a collection of N positive integers, you perform K operations like "half the biggest element and replace it with its own ceiling". Find the collection sum afterwards.
https://bintanvictor.wordpress.com/wp-admin/post.php?post=35955&action=edit
'''