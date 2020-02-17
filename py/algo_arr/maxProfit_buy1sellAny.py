'''
Avoid 32-bit integers. Prefer long integers.

'''
def trade1day(li, verbose=1):
  profit = 0
  buys = list() # the buy price levels
  theSellAfter = li[-1] # final price level
  if verbose: print "\n\t\t v v ", li
  for v in reversed(li):
    if v >= theSellAfter:
      assert abs(profit)<9223372036854775807, 'this int should be 64-bit signed'
      if verbose: 
        if profit: 
          print buys, theSellAfter, '==> profit reached', profit
        buys=list()
      theSellAfter = v
      continue
    assert v < theSellAfter
    # buy one share at $v, to be sold at $theSellAfter
    profit += (theSellAfter - v)
    if verbose: buys.append(v)

  print "\t\t ^ ^ returning", profit
  return profit
    
def test():
  assert 371 ==trade1day([120,1,2,100,2,119])
  assert 375 ==trade1day([1,2,100,2,120])
  assert 34 ==trade1day([2,10,0,12,2,7,1,6])
  tmp = [1 for _ in xrange(500000-1) ]
  tmp.append(100000)
  assert 499999*99999 ==trade1day(tmp, verbose=0)
  assert 0  ==trade1day([500000*100000, 500000*100000])
  assert 0  ==trade1day([50000])
  assert 2  ==trade1day([1,3,3,2])
  assert 11 ==trade1day([1,3,3,6])
  # 3 original test cases in HackerRank:
  assert 0  ==trade1day([5,3,2])
  assert 197==trade1day([1,2,100])
  assert 3  ==trade1day([1,3,1,2])
test()
''' Req: https://bintanvictor.wordpress.com/2018/06/08/day-trading-buy-1-sell-any-pimco/
'''
