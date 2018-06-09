
def trade(prices):
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
  assert 8 == trade([5,3,6,1,2])
  assert 8 == trade([5,6,1,2])
main()
'''Req: https://1330152open.wordpress.com/2018/06/09/to-landlord-self-intro/
Perhaps sort the data points and lose the order. Top half sell, bottom half buy.
'''
