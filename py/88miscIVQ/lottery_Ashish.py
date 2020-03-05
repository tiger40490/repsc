'''
showcase operator //

rename to hashCollide.py

Q: Is it possible that the winner for range 0-12345 is same as a simpler range?
Can we eliminate a big chunk of the range?

Q: once I build R8500, how best to build R28500? So far I need to shift R8500 to 20000-28500 first.

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
I decided to create classes to /cope/ with the potential increase in complexity. I may overestimate this increase and find a simpler solution, which doesn't need custom classes. Some programmers may dismiss the OO design as unnecessary and complicated, but at this moment, I don't know of any simple solution and OO should NOT complicate the situation.

Basic operation: join two ranges - adjacent non-overlapping ranges
Basic operation: shift a range up with prefix

Based on input range, we have pre-computed enough building blocks (Worry about the pre-compute later.)
bb99   bb199    bb299 ..
bb999  bb1999   bb2999 ..
bb9999 bb19999  bb29999 ..
Now for 0-28512, I already have bb19999 and need 20000-28512 
For 28000-28512, I expand bb499 to R512, then prefix the string '28'. So the frq table for 28000-20512 can be generated
For (easier) 20000-27999, I already have bb7999, so I prefix '2' to generate its frq table
'''
block=[0]*18 # the building blocks
class TicRange:
  def __init__(self,lo,hi):
    self.lo=lo
    self.hi=hi
    self.table=defaultdict(int)
  def do1ticket(self,tic):
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
  def checkCompletion(self):
    totalFrq = 0
    self.table = dict(self.table) # avoid defaultdict
    for k,v in self.table.iteritems():
      assert k >= 0 and v > 0
      totalFrq += v
    assert totalFrq == self.hi+1 - self.lo
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
  def clone(self, offset=0): # create a new frqtble (not a Block) of same size as self.table
      i = offset
      assert 0 <= i and i < 10, 'offset must be a single digit'
      scaling = 10**self.digits
      newtbl = TicRange(i*scaling, i*scaling+99)
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
  tbl = TicRange(100,199)
  b2 = block[2]
  for coupon, frq in b2.table.iteritems():
    tbl.table[coupon+1]=frq
  #print tbl
  tBl = block[2].clone(1)
  #print tBl
  assert tbl.table == tBl.table
def solveDP(lo,hi):
  block[2] = Block(2)
  for i in xrange(100):
    block[2].do1ticket(i)
  print block[2]

  block[3] = Block(3).build()
  # build as many blocks as the num of digits in hi  
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
'''Req: in a lottery each ticket has a positive int ID. It has a (non-unique) hashcode equal to the sum of its digits. The hashcode is also known as the coupon code of the ticket.

For a range of ticket IDs, find the ("hottest") hashcode with the largest population of tickets.

If the hottest hashcode has 55 colliding tickets, and there are 33 such hottest hashcodes, then return [33,55]. No need to return the actual hashcodes.
'''