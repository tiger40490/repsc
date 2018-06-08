# Note: Nsdq question has slightly different requirements but solution is completely different

def trade1day(li, verbose=1):
  profit = 0
  buys=list()
  theSellAfter=li[-1]
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
    profit += (theSellAfter - v)
    if verbose: buys.append(v)

  print "\t\t ^ ^ returning", profit
  return profit
    
def main():
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
main()
''' Req: Pimco Java HackerRank: Each minute, your high frequency trading platform allows 
you to either buy one share, sell any number of shares that you own, or not make any 
transaction at all. Your task is to find the maximum calc1BullRun you can obtain with 
an optimal trading strategy.

I remember having issues with some HackerRank test cases. Should use 64-bit int.
'''
