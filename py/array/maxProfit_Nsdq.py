# Insight -- original sequence of the price points don't matter, so we can sort them.
def solve(prices):
  sz = len (prices)
  smallHalf = sz/2
  ascending = sorted(prices)
  #print ascending
  buys = sells = profit = 0
  for i in xrange(sz):
    px = ascending[i]
    if i < smallHalf:
      #print 'buy $', px
      profit -= px
      buys += 1
    elif i > smallHalf or not sz%2: # not odd-sized
      #print 'sell $', px
      profit += px
      sells += 1
  assert buys == sells, 'buys and sells must tally'
  return profit

def main():
  assert 8 == solve([5,3,6,1,2])
  assert 8 == solve([5,6,1,2])
  assert 7 == solve([4,5,3,6,1])
  assert 9 == solve([4,5,3,6,1,2])
  assert 13 == solve([4,4,5, 4, 3, 4, 6,6,2,1,2])
main()
'''Req: https://bintanvictor.wordpress.com/2018/04/07/best-day-trading-play-in-hindsight-nasdaq/
'''
