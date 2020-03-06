'''
showcase Counter to merge two dictionaries
showcase inspect.stack() to get current function name
showcase calling superclass constructor
showcase operator //

todo: do1end last ticket 

rename to hashCollide_Ashish.py

Q: once I build R8500, how best to build R28500? So far I need to shift R8500 to 20000-28500 first.

(If we aim at the original smaller challenge) Q: Is it possible that the winner for range 0-12345 is same as a simpler range?
Can we eliminate a big chunk of the range?
'''
from collections import defaultdict, Counter 
from pprint import pprint
import inspect
log=1 # 0 means minimal; 1 means normal; 2 means verbose
def calcCoupon(tic):
  orig = tic # for debugging
  ret = 0
  while tic > 0:
    ret += tic%10
    tic //= 10
  #print orig, '->', 
  if log >=2 and orig%10 ==0: 
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
Basic operation: shift a range up with prefix.

These are hidden "constraints".

Based on input range, we pre-compute enough building blocks
bb99   bb199    bb299 ..
bb999  bb1999   bb2999 ..
bb9999 bb19999  bb29999 ..
Now for 0-28512, I already have bb19999 and need 20000-28512
For 28000-28512, I expand bb499 to R512, then prefix the string '28'. So the frq table for 28000-20512 can be generated
For (easier) 20000-27999, I already have bb7999, so I prefix '2' to generate its frq table
'''
block=[[0 for x in range(11)] for y in range(19)]# the building blocks
class TicRange:
  def __init__(self,lo,hi):
    self.lo=lo
    self.hi=hi
    self.table=defaultdict(int)
  def calc1ticket(self,tic):
    self.table[calcCoupon(tic)] += 1
  def subtract(self, otherTable):
    pass
  def clone(self, prefix): # create a new frqtble (not a Block) of same size as self.table
      assert 0 < prefix and prefix < 99999999999
      hi = int(str(prefix)+str(self.hi)) if self.hi else prefix
      newtbl = TicRange(hi-self.hi+self.lo, hi) # Shift-up logic !
      
      prefixCoupon=calcCoupon(prefix)
      for coupon, frq in self.table.iteritems():
        newtbl.table[coupon+prefixCoupon]=frq
      if log >= 2: 
        print newtbl
      else: 
        newtbl.checkCompletion()
      return newtbl
  def reconcile(self):
    if log > 0: print '('+str(self.lo)+'..'+str(self.hi), inspect.stack()[0][3],
    if self.hi > 99999: 
      if log > 0: print 'skippped)'
      return
    _, _, reference=buildFrqTable(self.lo, self.hi)
    assert reference == self.table
    if log > 0: print 'OK :)'
  def checkCompletion(self):
    totalFrq = 0
    self.table = dict(self.table) # avoid defaultdict
    for k,v in self.table.iteritems():
      if log >=3: print k,v
      assert k >= 0 and v > 0
      totalFrq += v
    assert (totalFrq == self.hi+1 - self.lo) , '%d..%d do not contain %d tickets'%(self.lo, self.hi, totalFrq) #valuable check!
    self.reconcile()
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
  def build(self): #buildFromPrevBlock
    pre = self.digits-1 
    assert block[pre][1]
    self.table = dict(block[pre][1].table)
    for i in xrange(1,10):
      tbl = block[pre][1].clone(i)
      self.table = dict(Counter(tbl.table) + Counter(self.table))
      if log >= 3: print self.table
    if log >=2: print self
    return self
  def cloneBigger(self, prefix1_9):
    assert 0 < prefix1_9 and prefix1_9 <= 9
    table = dict(block[self.digits][prefix1_9].table)
    tbl = block[self.digits][1].clone(prefix1_9)
    table = dict(Counter(tbl.table) + Counter(table))
    if log >= 3: print table
    hi = int(str(prefix1_9)+str(self.hi)) if self.hi else prefix1_9
    ret = TicRange(0, hi)
    ret.table = table
    if log > 0: print inspect.stack()[0][3] + "() returning", ret
    block[self.digits][prefix1_9+1] = ret
    return ret
def precomputeMatrix():
  block[0][1] = Block(0)
  block[0][1].calc1ticket(0)
  hiWaterMark=5
  for i in xrange(hiWaterMark):
    for j in xrange(1,10):
      block[i][1].cloneBigger(j)
    block[i+1][1] = Block(i+1).build()
      
  for i in xrange(hiWaterMark):
    for j in xrange(1,10):
      blk = block[i][j]
      cnt = len(blk.table)
      if log >= 1:
        print 'size-checking Mat[', i,j, ']: club size=',cnt, blk.lo, '..', blk.hi
      assert cnt      
def solveDP(lo,hi): #incomplete
  pass
def do1end(hi):
  precomputeMatrix()
  digits=list(str(hi))
  for w in range(1, 1+len(digits)):
    theDigit=digits[-w]
    blk = block[w-1][int(theDigit)]
    if log > 1: print 'blk=', blk
    prefix=''.join(digits[:-w])
    if theDigit=='0':
       prefix +='0'
    clone=blk.clone(int(prefix)) if prefix else blk
    print theDigit+'=theDigit, wei=', w, prefix, '=prefix',clone
  '''lowest digit is 2: block[0][2] clone(restOfDigits)
  '''
  print digits
def solve(lo,hi):
  print lo,hi,'->',
  return solveInLinearTime(lo, hi)
def testAll():
  do1end(38512) #512 has bug
  return
  blk = block[2][3]
  print '\n',blk
  print blk.clone(50)
  assert (1,2) == solve(1,10)
  assert (5,1) == solve(1,5)
  assert (1,2) == solve(3,12)
testAll()
'''Req: in a lottery each ticket has a positive int ID. It has a (non-unique) hashcode equal to the sum of its digits. The hashcode is also known as the coupon code of the ticket.

For a range of ticket IDs, find the ("hottest") hashcode with the largest population of tickets.

If the hottest hashcode has 55 colliding tickets, and there are 33 such hottest hashcodes, then return [33,55]. No need to return the actual hashcodes.

For a bigger challenge, try to generate the full histogram of all hashcodes.
'''