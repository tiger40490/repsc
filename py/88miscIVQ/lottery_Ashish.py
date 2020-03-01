from collections import defaultdict
from pprint import pprint
def calcCoupon(id):
  ret = 0
  while id > 0:
    ret += id%10
    id /= 10
  #print ret
  return ret
  
def solve(lo, hi):
  best = 1; ticketsForSameCoupon=defaultdict(list)
  for id in xrange(lo, hi+1):
    coupon = calcCoupon(id)
    ticketsForSameCoupon[coupon].append(id)
    best = max(best, len(ticketsForSameCoupon[coupon]))
  pprint(ticketsForSameCoupon)
  bestCoupons = 0; 
  for coupon, li in ticketsForSameCoupon.iteritems():
    if best == len(li):
      bestCoupons += 1
  return bestCoupons, best
def main():  
  assert (1,2) == solve(1,10)
  assert (5,1) == solve(1,5)
main()
'''Req: in a lottery each ticket has a positive int id. It has a (non-unique) coupon code equal to the sum of its digits.

For a range of ticket IDs, find the coupon code with the largest population of tickets
'''