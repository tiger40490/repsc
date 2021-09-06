'''
'''
globalVec = [1,3,7,2]
def myYieldFunctionList():
  for i in globalVec:
    yield i
def test2():
  gen6 = myYieldFunctionList()
  gen7 = myYieldFunctionList()
  next(gen6)
  next(gen6)
  print next(gen6), next(gen7)  
def myYieldFunction1():
  yield 'a'
  yield 'b'
  yield 'c'

def getGeneratorObj():
  retObj = myYieldFunction1()
  print type(retObj) # a generator object
  print dir(retObj) # shows __iter__() and next()
  return retObj
  
def test1():
  generator = getGeneratorObj()
  print next(generator), generator.next(), '------------'
  
  # now investating a builtin iterable object:
  rng = xrange(5)
  print dir(rng) # shows __iter__ not next()
  itr = iter(rng) 
  print dir(itr) #shows __iter__() and next()
test2()