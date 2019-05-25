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
  print 'after globeFunc()', id(globalInt), globalInt

  temp44=44
  assert id(temp44) == di['b4'], 'int obj id is based on int value'

  temp45=40+5
  assert id(temp45) == di['af'], 'int obj id is based on int value'

nonGlobal=40490
def simpleFunc(nonGlobal):
  #even though the id is same (due to value-based ref-counting) as the module-level nonGlobal, this local variable shadows the module-level
  print 'entering simpleFunc()', id(nonGlobal)
  nonGlobal += 1 # if no nonGlobal parameter, this line causes compilation error on the PREVIOUS line!
  print 'leaving simpleFunc()', id(nonGlobal), nonGlobal

def testLocal():
  print '\t vvvvv  testLocal() vvvvvv'
  print 'before simplFunc()', id(nonGlobal)
  simpleFunc(nonGlobal)
  assert nonGlobal == 40490, 'without global, the update is invisible after simpleFunc() returns'

testLocal()
testGlobal()
'''
This experiment shows int variable rebinding. The behavior is very different from java or c++.
'''