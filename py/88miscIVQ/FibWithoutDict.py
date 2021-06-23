fibNums=[0,1,1]
def fib(num):
  if num < len(fibNums): return fibNums[num]
  print 'computing #', num
  fibNums.append( fib(num-2)+fib(num-1) ) 
  ''' if num-1 on the Left, then the call graph looks different '''
  print 'done #', num
  return fibNums[-1]

expected = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34,55,89,144,233,377,610,987,1597,2584,4181,6765]  
def test(num):
  assert expected[num] == fib(num)
def main():
  test(20)
  print '-------------'
  test(19)
main()
'''This solution implements top-down DP with memoization using an array (pre-sized vector), rather than dict. Sounds like more daunting, but actually same complexity.

It turned out that we only need append and lookup, so hashtable is overkill
'''