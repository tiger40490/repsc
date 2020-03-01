'''
showcase operator //
'''
from collections import defaultdict
from pprint import pprint
def calcCoupon(tic):
  ret = 0
  while tic > 0:
    ret += tic%10
    tic //= 10
  #print ret
  return ret
  
def solve(lo, hi):
  maxClubSize = 0; 
  sameCouponTickets=defaultdict(list) #each dict Value is a club of tickets, having the same coupon code
  for tic in xrange(lo, hi+1):
    coupon = calcCoupon(tic)
    sameCouponTickets[coupon].append(tic) # ticket joins the correct club
    maxClubSize = max(maxClubSize, len(sameCouponTickets[coupon]))
  pprint(sameCouponTickets)
  
  howManyMaxClubs = 0; #count of clubs have the same max membership
  for coupon, li in sameCouponTickets.iteritems():
    if maxClubSize == len(li):
      howManyMaxClubs += 1
  return howManyMaxClubs, maxClubSize
def main():  
  assert (1,2) == solve(1,10)
  assert (5,1) == solve(1,5)
  assert (1,2) == solve(3,12)
main()
'''Req: in a lottery each ticket has a positive int tic. It has a (non-unique) coupon code equal to the sum of its digits.

For a range of ticket IDs, find the coupon code with the largest population of tickets
'''