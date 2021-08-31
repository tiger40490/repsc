'''
'''
def myYieldFunction1():
  yield 'a'
  yield 'b'
  yield 'c'

def getGeneratorObj():
  retObj = myYieldFunction1()
  print type(retObj) # a generator object
  print dir(retObj) # shows __iter__() and next()
  return retObj
  
def main():
  generator = getGeneratorObj()
  print next(generator), generator.next(), '------------'
  
  # now investating a builtin iterable object:
  rng = xrange(5)
  print dir(rng) # shows __iter__ not next()
  itr = iter(rng) 
  print dir(itr) #shows __iter__() and next()
main()