'''
todo:         assert self.size+1 < self.cap * self.loadfac

showcase passing a hashFunction as ctor argument
showcase populating a list with nested lists

I avoid the generi words index/position when 'bucket' is less ambiguous

Linear probing is one proven collision-resolution. Should be O(1) amortized for put/get/delete. 
High chance of hitting an empty bucket within 0 to 1 retries, provided load factor is low.
'''
class Hashmap:
  def __init__(self, hashFunc=hash, #hash() is good for int, string, float...
  capacity=4, maxLoadFactor=0.75):
    self.hasher=hashFunc
    self.cap=capacity; 
    self.loadfac=maxLoadFactor; 
    self.size=0; 
    self.arr= [[None, None]] * capacity
    #print 'in ctor', self.arr
  def getBucket(self, key):
    assert key is not None
    hashCode = self.hasher(key)
    hashCode = hash(hashCode) #rehash to guard against bad hasher, as in java
    return hashCode % self.cap 
  def incr(self,buc): return (1+buc)%self.cap
  def put(self, key, val): # return status
    buc = self.getBucket(key)
    while True:
      pair = self.arr[buc]
      if pair[0] is None: 
        if self.size+1 > self.cap * self.loadfac: self.expand()
        assert self.size+1 <= self.cap * self.loadfac
        self.arr[buc]=[key,val]
        self.size += 1
        return self.size
      if pair[0] == key: pair[1]=val; return -1 # existing key updated
      buc = self.incr(buc)

  def get(self, key): #return payload
    buc = self.getBucket(key)
    while True:
      pair = self.arr[buc]      
      if pair[0] is None: return None #special value to indicate invalid key
      if pair[0] == key: return pair[1]
      buc = self.incr(buc)
  def expand(self): #advanced feature 
    self.size = 0
    oldArr = self.arr
    self.cap *= 2
    self.arr = [[None, None]] * self.cap 
    #print self.arr, '||', oldArr, 'after swap'
    for key, val in oldArr:
       if key is not None: self.put(key, val)
    print '\nnew size =', self.size, 'after expand()', self.arr
    assert 2*(self.size +1) == self.cap

def doTestsPass():
  intList = [(1,12), (3,34), (5,56), (1,18), (2,25), (4,47)]
  strList = [("one", "two"), ("three", "four"), ("one", "five")]
  passed = True

  intMap = Hashmap()
  for key, value in intList:
    print 'adding', key, value, '-> ...', intMap.put(key, value)
    if intMap.get(key) != value:
      passed = False
      print "Test cased failed [", key, ",", value, "]"
  assert intMap.size == 5
  
  strMap = Hashmap()
  for key, value in strList:
    print 'adding', key, value, '->', strMap.put(key, value)
    if strMap.get(key) != value:
      passed = False
      print "Test cased failed [", key, ",", value, "]"
  assert strMap.size == 2

  if (passed):
    print("All tests passed.")
if __name__ == "__main__":
  doTestsPass()
"""Req by GS interviewer:
 * Associates a key-value pair in memory such that lookups
 * and inserts can be performed in O(1) time for a reasonably
 * small set of data, and scales linearly (at worst) for larger
 * sets of key-value pairs.
"""