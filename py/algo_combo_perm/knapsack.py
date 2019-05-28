'''
todo: early exit at first S=0?
todo: automated tests

showcase class attribute
showcase defaultdict(int)
showcase memoization using dict as key -- need to use the string version of it.

Simple and clean logic to support limited or unlimited availability.

My knapsack greedy() is similar to comboSum.cpp without 'startIndex' param. 
I believe startIndex complicates memoization a bit. Not sure if the startIndex version is more efficient for knapsack problem
'''
from collections import defaultdict
from pprint import pprint
class Obj:
  nextId=65 #class attribute
  names=dict()
  def __init__(self, val, weight, avail, id=0):
    self.v = val
    self.w = weight
    self.d = val/float(weight) #density
    self.a = avail #available count.. mutable
    if id==0:
      self.id = chr(Obj.nextId)
      Obj.nextId+=1
    else: self.id=id
    Obj.names[self.id]=self.v
  def __str__(self):
    return "{"+self.id+" x"+str(self.a) + ' $' \
      +str(self.v)+'/'+str(self.w)+' kg}'
  def __repr__(self): return str(self) #needed by list printing
memo=dict()
def greedy(li, S, bag):
  ''' returns the smallest stub capacity that can't be used. If stub is 0 then successful
  
  greedy as it bags the "highest density" first.
  
  As a job function, this func needs to try all combinations for a given li and S, always starting with the densest object
  '''
  memoKey=(S, str(dict(bag)))
  if memoKey in memo: return memo[memoKey], memo['besttotal']
  print '-> S=', S, dict(bag)
  stub=S
  for obj in li:
    if obj.a <= 0: continue
    if obj.w > S: continue
    bag[obj.id] +=1; obj.a -= 1
    newStub, _ = greedy(li, S-obj.w, bag)
    if stub > newStub:
       stub = newStub
    bag[obj.id] -=1; obj.a += 1 #restore
    if bag[obj.id] == 0: del bag[obj.id]
  if stub == S:
    total=0
    for id,cnt in bag.iteritems():
      total += Obj.names[id] * cnt      
    print '<- Leaf node. total value = $', total
    if memo['besttotal'] < total:
       memo['besttotal'] = total
    if S==0: print '00000 ... perhaps should terminate the recursion?'
  memo[memoKey] = stub
  return stub, memo['besttotal']
def dp(li, S=7):
  pool=sorted(li, reverse=True, key=lambda i: i.d)
  memo.clear(); memo['besttotal']=0
  print '  v v  entering dp() with', pool
  bag=defaultdict(int)
  greedy(li, S, bag)
  print '  ^ ^  returning from dp() with memo ='
  pprint (memo)
def test():
  dp( [Obj(6,3,1), Obj(3,2,1,'b'), Obj(2,2,99,'c') ] )
test()
'''Req: knapsack problem: we are given a fixed set of n items, where each item i is specified by an available count a[i], weight w[i] and value v[i]. 
We are also given a weight bound W (i.e. capacity of knapsack). 
The optimization goal is to find the subset of items of maximum total value such that total weight is at most W (they don't break the knapsack)
'''