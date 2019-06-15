def globeFunc():
  global globalInt
  print 'entering globeFunc()', id(globalInt)
  assert id(globalInt) == di['b4']
  globalInt +=1
  di['af'] = id(globalInt)
  assert id(globalInt) != di['b4']
  print 'leaving globeFunc()', id(globalInt)

globalInt=44
di=dict()
def testGlobal():
  print '\t vvvvv  testGlobal() vvvvvv'
  print 'before globeFunc()', id(globalInt)
  di['b4'] = id(globalInt)
  globeFunc()
  assert di['af'] == id(globalInt)
  assert di['af'] != di['b4']
  print 'after globeFunc()', id(globalInt), globalInt

  temp44=44
  assert id(temp44) == di['b4'], 'int obj id is based on int value, like java string intern'

  temp45=40+5
  assert id(temp45) == di['af'], 'int obj id is based on int value, like java string intern'
##############
nonGlobal=40490
def simpleFunc(nonGlobal):
  #even though the id is same (due to value-based ref-counting) as the module-level nonGlobal, this local variable overshadows the module-level variable of the same name
  print id(nonGlobal), 'entering simpleFunc()'
  nonGlobal += 1 # if nonGlobal is not a function parameter, this line would cause compilation error on the PREVIOUS line!
  print id(nonGlobal), 'leaving simpleFunc()', nonGlobal

def testLocal():
  print '\t vvvvv  testLocal() vvvvvv'
  print 'before simplFunc()', id(nonGlobal)
  simpleFunc(nonGlobal)
  assert nonGlobal == 40490, 'Since simpleFunc() does not use q[global], the update is invisible after simpleFunc() returns'

testGlobal()
testLocal()
'''
This experiment shows int variable rebinding. Python behavior is very different from java or c++.
'''