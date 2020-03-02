'''
showcase operator //

todo: build the support for creating a FrqTable(300,399)
todo: build support for creating Block(3)
rename to ...
'''
from collections import defaultdict, Counter 
from pprint import pprint
def calcCoupon(tic):
  orig = tic # for debugging
  ret = 0
  while tic > 0:
    ret += tic%10
    tic //= 10
  #print orig, '->', 
  if False and orig%10 ==0: 
    cnt=ret-1 #(orig/10)%10
    print '  (%d..%d)\n' % (orig-10,orig-1),
    print '   '*cnt,
  #print "%2d"%ret,
  return ret
def solveInLinearTime(lo, hi):
  maxClubSize = 0; 
  sameCouponTickets=defaultdict(list) #each dict Value is a club of tickets, having the same coupon code
  for tic in xrange(lo, hi+1): # O(N) loop for N tickets
    coupon = calcCoupon(tic)
    sameCouponTickets[coupon].append(tic) # ticket joins the correct club
    maxClubSize = max(maxClubSize, len(sameCouponTickets[coupon]))
  print
  #pprint(sameCouponTickets)
  
  howManyMaxClubs = 0; #count of clubs have the same max membership
  for coupon, li in sameCouponTickets.iteritems(): #O(C) loop for C unique coupon codes
    if maxClubSize == len(li):
      howManyMaxClubs += 1
  return howManyMaxClubs, maxClubSize

'''
First bulid frq table like {coupon: frq} for 0 to 99. Call it F2 i.e. table for 2-digit tickets
If we need tickets 300~309, then the frq table for this range can be built using F2. 
For hashcode 5, frq(5)=F2[5-3]. 
For hashcode 3, frq(3)=1
For hashcode 3+9+9, frq(22) = F2[22-3]

Therefore, we can build F3 frq table in 10 x len(F2)

'''
block=[0]*18 # the building blocks
class FrqTable:
  def __init__(self,lo,hi):
    self.lo=lo
    self.hi=hi
    self.table=defaultdict(int)
  def addtic(self,tic):
    self.table[calcCoupon(tic)] += 1
  def checkCompletion(self):
    totalFrq = 0
    self.table = dict(self.table) # avoid defaultdict
    for k,v in self.table.iteritems():
      totalFrq += v
    assert totalFrq == self.hi+1 - self.lo
    return totalFrq
  def __str__(self):
    ret = '%d..%d: %d ' % (self.lo, self.hi, self.checkCompletion())
    ret += str(self.table)
    return ret
class Block(FrqTable):
  def __init__(self,digits):
    hi = -1+10**(digits) #3-digit .. 999
    FrqTable.__init__(self, 0, hi)
    self.digits = digits
  def clone(self, offset): # create a new frqtble (not a Block) of same size as self.table
      i = offset
      assert 0 < i and i < 10, 'offset must be a single digit'
      scaling = 10**self.digits
      newtbl = FrqTable(i*scaling, i*scaling+99)
      for coupon, frq in block[self.digits].table.iteritems():
        newtbl.table[coupon+i]=frq
      #print tbl
      return newtbl
  def build(self):
    pre = self.digits-1 
    assert block[pre]
    self.table = dict(block[pre].table)
    for i in xrange(1,10):
      tbl = block[pre].clone(i)
      print tbl
      self.table = dict(Counter(tbl.table) + Counter(self.table))
      #print self.table
    print self
    return self
    
def test():
  tbl = FrqTable(300,399)
  b2 = block[2]
  for coupon, frq in b2.table.iteritems():
    tbl.table[coupon+3]=frq
  print tbl  
  tBl = block[2].clone(3)
  print tBl
  assert sorted(tbl.table.keys()) == sorted(tBl.table.keys())
  assert sorted(tbl.table.values()) == sorted(tBl.table.values())
def solveDP(lo,hi):
  block[2] = Block(2)
  for i in xrange(100):
    block[2].addtic(i)
  print block[2]

  block[3] = Block(3).build()
  
def solve(lo,hi):
  return solveInLinearTime(lo, hi)
def main():
  solveDP(0,321)  
  test()
  return
  assert (1,2) == solve(1,10)
  assert (5,1) == solve(1,5)
  assert (1,2) == solve(3,12)
  solve(79,1141)
main()
'''Req: in a lottery each ticket has a positive int ID. It has a (non-unique) hashcode equal to the sum of its digits. The hashcode is also known as the coupon code.

For a range of ticket IDs, find the ("hottest") hashcode with the largest population of tickets.
'''