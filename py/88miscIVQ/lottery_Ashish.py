'''
showcase collections.Counter to merge two dictionaries
showcase inspect.stack() to get current function name
showcase calling superclass constructor
showcase operator //
showcase: The global matrix of TicRange objects greatly simplifies implementation, though global variables are considered a code smell. I feel this is a legitimate design choice.

todo: simplify. Still feels too complicated but this is a lot better than the initial versions.
todo: more sanity checks

rename to hashCollide_Ashish.py

(If we aim at the original smaller challenge) Q: Is it possible that the winner for range 0-12345 is same as a simpler range?
Can we eliminate a big chunk of the range?
'''
from collections import defaultdict, Counter 
from pprint import pprint
import inspect
log=1 # 0 means minimal; 1 means normal; 2 means verbose
def calcHash(tic):
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
    coupon = calcHash(tic)
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
    self.hi=int(hi)
    self.table=defaultdict(int)
  def calc1ticket(self,tic):
    self.table[calcHash(tic)] += 1
  def subtract(self, otherTable):
    pass
  def clone(self, longPrefix): # create a new TicRange (not a Block) of same size as self
      assert 0 < longPrefix and longPrefix < 99999999999999
      high = int(str(longPrefix)+str(self.hi)) if self.hi else longPrefix
      newtbl = TicRange(high-self.hi+self.lo, high) # Shift-up logic !
      
      prefixCoupon=calcHash(longPrefix)
      for coupon, frq in self.table.iteritems():
        newtbl.table[coupon + prefixCoupon]=frq
      
      if log >= 2: print newtbl
      else: newtbl.checkCompletion()
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
  def __init__(self,digitCnt):
    hi = -1+10**(digitCnt) #3-digit .. 999
    TicRange.__init__(self, 0, hi)
    self.digitCnt = digitCnt
  def build(self): #buildTbl
    pre = self.digitCnt-1 
    assert block[pre][1]
    self.table = dict(block[pre][1].table)
    for i in xrange(1,10):
      tbl = block[pre][1].clone(i)
      hi2 = '9'*(self.digitCnt-1)
      block[pre][i+1] = tmp2 = TicRange(0, str(i)+hi2)
      self.table = tmp2.table = dict(Counter(tbl.table) + Counter(self.table))
      if log > 1: print tmp2
      
    if log >=2: print self
    block[self.digitCnt][1]=self
def precomputeMatrix():
  if block[2][10]: return
  block[0][1] = Block(0)
  block[0][1].calc1ticket(0)
  hiWaterMark=5
  for i in xrange(1, hiWaterMark+1):
    Block(i).build()
      
  # verify
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
  segments=list()
  for w in range(1, 1+len(digits)): 
    theDigit=digits[-w] #w means radix position
    if theDigit == '0': continue      
    
    blk = block[w-1][int(theDigit)]
    prefix=''.join(digits[:-w])
    if theDigit=='1':
       prefix +='0'
    if log >1: print prefix, '=prefix, blk=', blk
    clone=blk.clone(int(prefix)) if prefix else blk
    segments.insert(0,clone)
    if log: print theDigit+'=theDigit, wei=', w, prefix, '=prefix',clone
  
  last=segments[-1] # add the highest ticket
  last.table = defaultdict(int, last.table)
  last.hi=hi
  last.calc1ticket(hi)
  if log: print last

  # verify
  print digits
  for c in xrange(1,len(segments)):
     assert segments[c-1].hi +1 == segments[c].lo, '%d+1!=%d' %(segments[c-1].hi +1, segments[c].lo)
  
  # add up
  allSeg = Counter()
  for seg in segments:
    allSeg += Counter(seg.table)
  # reconcile
  _,_,expected = buildFrqTable(0,hi)
  print 'buildFrqTable() returned', expected
  print 'allSeg =',allSeg
  assert allSeg == expected
  
def solve(lo,hi):
  print lo,hi,'->',
  return solveInLinearTime(lo, hi)
def testAll():
  do1end(38011)
  do1end(38001)
  do1end(3800)
  return
  assert (1,2) == solve(1,10)
  assert (5,1) == solve(1,5)
  assert (1,2) == solve(3,12)
testAll()
'''Req: in a lottery each ticket has a positive int ID. It has a (non-unique) hashcode equal to the sum of its digits. The hashcode is also known as the coupon code of the ticket.

For a range of ticket IDs, find the ("hottest") hashcode with the largest population of tickets.

If the hottest hashcode has 55 colliding tickets, and there are 33 such hottest hashcodes, then return [33,55]. No need to return the actual hashcodes.

For a bigger challenge, try to generate the full histogram of all hashcodes.
'''