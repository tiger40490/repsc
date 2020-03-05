'''
showcase inspect.stack() to get current function name
showcase calling superclass constructor
showcase operator //

rename to hashCollide.py

Q: once I build R8500, how best to build R28500? So far I need to shift R8500 to 20000-28500 first.

(If we aim at the original smaller challenge) Q: Is it possible that the winner for range 0-12345 is same as a simpler range?
Can we eliminate a big chunk of the range?
'''
from collections import defaultdict, Counter 
from pprint import pprint
import inspect
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
  print inspect.stack()[0][3]
  sameCouponTickets, maxClubSize,_ = buildFrqTable(lo,hi)
  howManyMaxClubs = 0; #count of clubs have the same max membership
  for coupon, li in sameCouponTickets.iteritems(): #O(C) loop for C unique coupon codes
    if maxClubSize == len(li):
      howManyMaxClubs += 1
  return howManyMaxClubs, maxClubSize
def buildFrqTable(lo, hi):
  maxClubSize = 0; 
  frqTable=defaultdict(int)
  sameCouponTickets=defaultdict(list) #each dict Value is a club of tickets, having the same coupon code
  for tic in xrange(lo, hi+1): # O(N) loop for N tickets
    coupon = calcCoupon(tic)
    frqTable[coupon] += 1
    sameCouponTickets[coupon].append(tic) # ticket joins the correct club
    maxClubSize = max(maxClubSize, len(sameCouponTickets[coupon]))
  #print
  #pprint(sameCouponTickets)
  return sameCouponTickets, maxClubSize,frqTable
'''
I decided to create classes to /cope/ with the potential increase in complexity. I may overestimate this increase and find a simpler solution, which doesn't need custom classes. Some programmers may dismiss the OO design as unnecessary and complicated, but at this moment, I don't know of any simple solution and OO should NOT complicate the situation.

Basic operation: join two ranges - adjacent non-overlapping ranges
Basic operation: shift a range up with prefix

Based on input range, we have pre-computed enough building blocks
bb99   bb199    bb299 ..
bb999  bb1999   bb2999 ..
bb9999 bb19999  bb29999 ..
Now for 0-28512, I already have bb19999 and need 20000-28512
For 28000-28512, I expand bb499 to R512, then prefix the string '28'. So the frq table for 28000-20512 can be generated
For (easier) 20000-27999, I already have bb7999, so I prefix '2' to generate its frq table
'''
block=[[0 for x in range(10)] for y in range(19)]# the building blocks
class TicRange:
  def __init__(self,lo,hi):
    self.lo=lo
    self.hi=hi
    self.table=defaultdict(int)
  def calc1ticket(self,tic):
    self.table[calcCoupon(tic)] += 1
  def shift(self, prefix): # untested
    # eg: prefix 20 to 500 ->20500
    tmp = prefix
    while tmp > 9:
      assert tmp % 10 > 0
      tmp /= 10
    assert tmp < 10, 'prefix must be a single digit followed by optional zeros'
    #self.lo += offset
    #self.hi += offset 
    #self.table = dict(Counter(self.table) + Counter(otherTable.table))
  def subtract(self, otherTable):
    pass
  def verify(self):
    print '(' + inspect.stack()[0][3],
    if self.hi > 99999: 
      print 'skippped)'
      return
    _, _, reference=buildFrqTable(self.lo, self.hi)
    assert reference == self.table
    print 'OK :)'
  def checkCompletion(self):
    totalFrq = 0
    self.table = dict(self.table) # avoid defaultdict
    for k,v in self.table.iteritems():
      #print k,v
      assert k >= 0 and v > 0
      totalFrq += v
    #print totalFrq, self.hi, self.lo
    assert totalFrq == self.hi+1 - self.lo
    self.verify()
    return totalFrq
  def __str__(self):
    ret = '%d..%d: %d ' % (self.lo, self.hi, self.checkCompletion())
    ret += str(self.table)
    return ret
class Block(TicRange):
  def __init__(self,digits):
    hi = -1+10**(digits) #3-digit .. 999
    TicRange.__init__(self, 0, hi)
    self.digits = digits
  def clone(self, offset): # create a new frqtble (not a Block) of same size as self.table
      i = offset
      assert 0 <= i and i < 10, 'offset must be a single digit'
      hi = int(str(i)+str(self.hi)) if self.hi else i
      newtbl = TicRange(hi-self.hi, hi)
      for coupon, frq in block[self.digits][0].table.iteritems():
        newtbl.table[coupon+i]=frq
      print newtbl
      return newtbl
  def build(self): #buildFromPrevBlock
    pre = self.digits-1 
    assert block[pre][0]
    self.table = dict(block[pre][0].table)
    for i in xrange(1,10):
      tbl = block[pre][0].clone(i)
      self.table = dict(Counter(tbl.table) + Counter(self.table))
      #print self.table
    print self
    return self
def precomputeMatrix():
  block[0][0] = Block(0)
  block[0][0].calc1ticket(0)
  hiWaterMark=5
  for i in xrange(hiWaterMark):
    for j in xrange(1,10):
      block[i][j]=block[i][0].clone(j)
    block[i+1][0] = Block(i+1).build()
      
  for i in xrange(hiWaterMark):
    for j in xrange(10):
      blk = block[i][j]
      cnt = len(blk.table)
      print 'size-checking [', i,j, ']: club size=',cnt, blk.lo, '..', blk.hi
      assert cnt      
def solveDP(lo,hi): #incomplete
  pass
  # build as many blocks as the num of digits in hi  
def solve(lo,hi):
  print lo,hi,'->',
  return solveInLinearTime(lo, hi)
def main():
  precomputeMatrix()
  #test(); 
  return
  assert (1,2) == solve(1,10)
  assert (5,1) == solve(1,5)
  assert (1,2) == solve(3,12)
main()
'''Req: in a lottery each ticket has a positive int ID. It has a (non-unique) hashcode equal to the sum of its digits. The hashcode is also known as the coupon code of the ticket.

For a range of ticket IDs, find the ("hottest") hashcode with the largest population of tickets.

If the hottest hashcode has 55 colliding tickets, and there are 33 such hottest hashcodes, then return [33,55]. No need to return the actual hashcodes.

For a bigger challenge, try to generate the full histogram of all hashcodes.
'''