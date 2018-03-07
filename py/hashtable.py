# todo: rehash

class Node:
  def __init__(self, _k, _data, _next):
    self.next = _next
    self.key = _k
    self.val = _data
  def __str__(self):
    return '[ '+ str(self.key) + ':' + str(self.val) + ' ]'
def hash(key):
   return key*13
   
class Hashtable:
  def __init__(self, _bc=10, _lf=0.75):
    self.sz = 0
    self.bucketcnt = _bc
    self.arr=list()
    for _ in range(self.bucketcnt):
      self.arr.append(None)
    
    # when size/bucketcnt grows to loadfactor, we need to 
    # double the array, and re-distribute the elements
    self.loadfactor = _lf

  def dump(self):
    print '------ sz = %d ------' %self.sz
    for i in range(self.bucketcnt):
      node = self.arr[i]
      if node is None: continue
      print 'Bucket #',i, node,
      while True:
        node = node.next
        if node is None: break
        print '->', node,
      print 
      
  def _lookup(self, k): # returns associated value or something else
    index = hash(k)% self.bucketcnt
    node = self.arr[index]
    while True:
      if node is None: return index # insert here
      if node.key == k: return node
      node = node.next

  def lookup(self, k):
    node = self._lookup(k)
    if isinstance(node, Node): return node.val
    return None

  def insert(self, k, v): # if val is already in then don't insert
    nodeOrIndex = self._lookup(k)
    if isinstance(nodeOrIndex, Node): return False
    #print 'old head is', id(self.arr[nodeOrIndex])
    ret = Node(k,v,self.arr[nodeOrIndex])
    self.arr[nodeOrIndex] = ret
    assert ret != ret.next
    #print 'new head is', id(ret), ret
    #print 'new 2nd is', id(ret.next), ret.next
    #print 'new 3rd is', id(ret.next.next)
    self.sz += 1
    return ret
def main():
  h = Hashtable()
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
  assert not h.insert(3,'33')
  h.dump()
main()
'''Requirement: implement a basic hashtable within 30 min
5.20
'''