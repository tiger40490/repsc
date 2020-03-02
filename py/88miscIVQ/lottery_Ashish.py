'''
showcase operator //

rename to ...
'''
from collections import defaultdict
from pprint import pprint
def calcCoupon(tic):
  orig = tic # for debugging
  ret = 0
  while tic > 0:
    ret += tic%10
    tic //= 10
  #print orig, '->', 
  if orig%10 ==0: 
    cnt=ret-1 #(orig/10)%10
    print '  (%d..%d)\n' % (orig-10,orig-1),
    print '   '*cnt,
  print "%2d"%ret,
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
If we need 301~309, then the frq table for this range be built using F2. 
For coupon 5, frq(5)=F2[5-3]. 
For coupon 3, frq(3)=0
For coupon 3+9+9, frq(22) = F2[22-3]

Therefore, we can build F3 frq table in 10 x len(F2)

'''
def solveDP(lo,hi):
  pass  
  
def solve(lo,hi):
  return solveInLinearTime(lo, hi)
def main():  
  assert (1,2) == solve(1,10)
  assert (5,1) == solve(1,5)
  assert (1,2) == solve(3,12)
  solve(79,1141)
main()
'''Req: in a lottery each ticket has a positive int ID. It has a (non-unique) hashcode equal to the sum of its digits.

For a range of ticket IDs, find the ("hottest") hashcode with the largest population of tickets.
'''