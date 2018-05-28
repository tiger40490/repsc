def trade1day(li):
  holding=0; cashflow=0
  for i in xrange(len(li)-1): # visit all but last point
    #print li[i]
    if li[i]<=li[i+1]:
      print 'buy 1 @', li[i]
      holding += 1
      cashflow -= li[i]
    else: 
      if holding: # trivial optimization
        print 'sell', holding, '@', li[i]
        cashflow += holding * li[i]
        holding=0

  print 'Last point: sell', holding, '@', li[-1]
  cashflow += holding * li[-1]
  return cashflow
def main():
  assert 2  ==trade1day([1,3,3,2])
  assert 11 ==trade1day([1,3,3,6])
  # 3 original test cases in HackerRank:
  assert 0  ==trade1day([5,3,2])
  assert 197==trade1day([1,2,100])
  assert 3  ==trade1day([1,3,1,2])
main()
''' Req: Pimco Java HackerRank: Each minute, your high frequency trading platform allows you to either buy one share, sell any number of shares that you own, or not make any transaction at all. Your task is to find the maximum profit you can obtain with an optimal trading strategy.

I remember having issues with some HackerRank test cases.
'''