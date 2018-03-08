''' todo: delete(). update() can be implemented by delete() then insert()

showcase: initialize a list of 5 None items
showcase: __str__() to facilitate "print"
'''
class Node:
  def __init__(self, _k, _data, _next):
    self.next = _next
    self.key = _k
    self.val = _data
  def __str__(self):
    return '[ '+ str(self.key) + ':' + str(self.val) + ' ]'

def hash(key): # simple hash function
   return key*73
   
class HashTable:
  def __init__(self, _bc=10, _lf=0.75):
    self.sz = 0
    self.bucketCnt = _bc
    self.arr = [None] * self.bucketCnt
    
    # when size/bucketCnt grows to exceed loadfactor, we need to 
    # double the array, and re-distribute all elements
    self.loadfactor = _lf

  def dump(self):
    print '------ sz = %d ------' %self.sz
    for i in range(self.bucketCnt):
      node = self.arr[i]
      if node is None: continue
      print 'Bucket #',i, node,
      while True:
        node = node.next
        if node is None: break
        print '->', node,
      print 
      
  def rehash(self):
    if self.sz < self.loadfactor*self.bucketCnt : return
    print "REHASHING.... Here is the before-image:",
    self.dump()
    
    #oldCnt = self.bucketCnt
    oldArr = self.arr
    self.sz=0
    self.bucketCnt *= 2
    self.arr = [None] * self.bucketCnt
    for i in range(self.bucketCnt/2):
      node = oldArr[i]
      while True:
        if node is None: break
        self.insert(node.key, node.val)
        node = node.next
    print '... done with rehashing:)'
    
  def _lookup(self, k): # returns associated value or something to indicate notFound
    index = hash(k)% self.bucketCnt
    node = self.arr[index]
    while True:
      if node is None: return index # insert here
      if node.key == k: return node
      node = node.next

  def lookup(self, k):
    node = self._lookup(k)
    if isinstance(node, Node): return node.val
    return None

  def insert(self, k, v): # if val is already in then return False
    nodeOrIndex = self._lookup(k)
    if isinstance(nodeOrIndex, Node): return False
    self.rehash()
    #print 'old head is', id(self.arr[nodeOrIndex])
    ret = Node(k,v,self.arr[nodeOrIndex])
    self.arr[nodeOrIndex] = ret
    self.sz += 1
    #print 'new head is', id(ret), ret
    #print 'new 2nd is', id(ret.next), ret.next
    #print 'new 3rd is', id(ret.next.next)
    return ret
def main():
  h = HashTable()
  h.dump()
  assert h.insert(1,'aa')
  assert h.insert(2,'b')
  assert h.insert(3,'c')
  assert h.insert(4,'d')
  assert h.insert(5,'e')
  assert h.insert(6,'f')
  assert h.insert(7,'g')
  assert h.insert(8,'h')
  assert h.insert(9,'i')
  assert h.insert(10,'j')
  assert h.insert(11,'k')
  assert h.insert(14,'n')
  assert h.insert(21,'u')
  assert not h.insert(3,'newValue')
  assert 'aa' == h.lookup(1)
  h.dump()
main()
'''Requirement: implement a basic hashtable within 30 min
'''
