'''
Linear probing is one proven collision-resolution. Should be O(1) amortized for put/get/delete. 
High chance of hitting an empty bucket within 0 to 1 retries, provided load factor is low.
'''
class Hashmap:
  def __init__(self, capacity=4, maxLoadFactor=0.75):
    self.size=0; 
    self.cap=capacity; 
    self.loadfac=maxLoadFactor; 
    self.arr=[[None, None]] * capacity
    #print 'in ctor', self.arr
  def myHash(self, key):
    return hash(key) #use python hash() for int, string, float...
  def incr(self,buc): return (1+buc)%self.cap
  def put(self, key, val):
    buc = self.myHash(key)%self.cap
    while True:
      aa = self.arr[buc]
      if aa[0] is None: 
        self.arr[buc]=[key,val]; 
        self.size += 1; 
        if self.size > self.cap * self.loadfac: self.expand()
        assert self.size <= self.cap * self.loadfac
        return 1 # inserted
      if aa[0] == key: aa[1]=val; return 2 # existing key updated
      buc = self.incr(buc)

  def get(self, key): #return payload
    buc = self.myHash(key)%self.cap
    while True:
      aa = self.arr[buc]      
      if aa[0] is None: return None #special value to indicate invalid key
      if aa[0] == key: return aa[1]
      buc = self.incr(buc)
  def expand(self): 
    self.size = 0
    otherArr = self.arr
    self.cap *= 2
    self.arr = [[None, None]] * self.cap 
    #print self.arr, '||', otherArr, 'after swap'
    for key, val in otherArr:
       self.put(key, val)
    print 'after expand()', self.arr

def doTestsPass():
  intList = [(1,12), (3,34), (5,56), (1,18), (2,25), (4,47)]
  strList = [("one", "two"), ("three", "four"), ("one", "five")]
  passed = True

  intMap = Hashmap()
  for key, value in intList:
    print 'adding', key, value, '->', intMap.put(key, value)
    if intMap.get(key) != value:
      passed = False
      print ("Test cased failed [", key, ",", value, "]")
  assert intMap.size == 5
  
  strMap = Hashmap()
  for key, value in strList:
    print 'adding', key, value, '->', strMap.put(key, value)
    if strMap.get(key) != value:
      passed = False
      print("Test cased failed [", key, ",", value, "]")
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