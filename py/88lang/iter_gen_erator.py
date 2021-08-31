def myYieldFunction1():
  yield 'a'
  yield 'b'
  yield 'c'

def main():
  retObj = myYieldFunction1()
  print type(retObj) # a generator
  print dir(retObj) # shows __iter__() and next()
  print next(retObj), retObj.next() 
  
  # now investating a builtin iterable object:
  rng = xrange(5)
  itr = iter(rng) 
  print dir(itr) #shows __iter__() and next()
main()