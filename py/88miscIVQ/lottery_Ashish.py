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
    print '\n', '   '*(orig/10-10),
  print "%2d"%ret,
  return ret
  
def solve(lo, hi):
  maxClubSize = 0; 
  sameCouponTickets=defaultdict(list) #each dict Value is a club of tickets, having the same coupon code
  for tic in xrange(lo, hi+1): # O(N) loop for N tickets
    coupon = calcCoupon(tic)
    sameCouponTickets[coupon].append(tic) # ticket joins the correct club
    maxClubSize = max(maxClubSize, len(sameCouponTickets[coupon]))
  print
  pprint(sameCouponTickets)
  
  howManyMaxClubs = 0; #count of clubs have the same max membership
  for coupon, li in sameCouponTickets.iteritems(): #O(C) loop for C unique coupon codes
    if maxClubSize == len(li):
      howManyMaxClubs += 1
  return howManyMaxClubs, maxClubSize
def main():  
  #assert (1,2) == 
  solve(99,151)
  return
  assert (5,1) == solve(1,5)
  assert (1,2) == solve(3,12)
main()
'''Req: in a lottery each ticket has a positive int tic. It has a (non-unique) coupon code equal to the sum of its digits.

For a range of ticket IDs, find the coupon code with the largest population of tickets
'''