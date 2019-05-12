'''
todo: test combo with non-stirngs
Q: what if the pool has dupes? 
A: I think simplest solution uses a dictionary. I feel there's no need to fight this battle
'''
import sys,itertools
def _com(func, items, howManyMore, logLevel=0): 
#internal recursive generator function to generate all subsets of items, each in a list of length = howManyMore
  if howManyMore==0: yield []; return #recursion exit condition
  assert howManyMore > 0
  indent = (3-howManyMore)*'  '
  for pos,val in enumerate(items):
    listLedByVal = [val]
    if logLevel: print indent, 'listLedByVal =',val
      
    # func is a two-arg callable that returns a subset
    for newList in _com(func, func(items,pos), howManyMore-1, logLevel): #recurse down
      if logLevel: print indent, listLedByVal + newList
      yield listLedByVal + newList #concat 2 lists
def abbr(word, n): #generates all abbreviations of length==n
  def after_i_th_item(pool,pos):
    return pool[pos+1:]
  return _com(after_i_th_item, word,n) #,True)
def allAbbr(word):
  gen = itertools.chain()
  for n in xrange(1+len(word)):
    gen = itertools.chain(gen, abbr(word,n))
  return gen
def redraw(pool, n): # redraw n times from same pool. If pool size=55, then 55^n outcomes
  def keepAll(pool,_): return pool
  return _com(keepAll, pool, n) #, True)
def combo(pool, n): #preserves original order
  def after_i_th_item(pool,pos):
    return pool[pos+1:]
  return _com(after_i_th_item, pool,n) #,True)
def subsetPerm(pool, n): #accepts distinct items
  def skip_i_th_Item(pool, pos):
    return pool[:pos] + pool[pos+1:]
  return _com(skip_i_th_Item, pool, n)#, True)# returns generator object, to be used in iteration context
def testRedraw():
  print '  v v  --  redraw  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abc'
  for out in redraw(nonRepeat, 2):
    word = ''.join(out)
    fmt2 += word + ' '
    fmt1 += str(out)
    cnt += 1
    unique[word]=1
  print fmt2, fmt1
  assert len(unique)==len(nonRepeat)**2==cnt
def testAbbr():
  print '  v v  --  abbr  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abcd'
  for out in allAbbr(nonRepeat): #, 3):
    word = ''.join(out)
    fmt2 += word + '; '
    fmt1 += str(out)
    cnt += 1
    unique[word]=1
  print fmt2 #, fmt1
  assert len(unique)==2**len(nonRepeat)==cnt
def testCombo():
  print '  v v  --  combo  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat=[1,2,3,4,5,6,7]
  for out in combo(nonRepeat, 3):
    word = ''.join(str(i) for i in out)
    fmt2 += word + ' '
    fmt1 += str(out)
    cnt += 1
    unique[word]=1
  print fmt2
  assert len(unique)==7*6*5/3/2==cnt
def testPerm():
  print '  v v  --  subsetPerm  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abcd'
  for out in subsetPerm(nonRepeat, 2):
    word = ''.join(out)
    fmt2 += word + ' '
    fmt1 += str(out)
    cnt += 1
    unique[word]=1
  print fmt2, fmt1
  assert len(unique)==12==cnt
  
  li=list(subsetPerm(nonRepeat, len(nonRepeat))) #full permutation
  unique=dict(enumerate(li))
  assert len(unique)==24==len(li)
def main():
  testPerm()
  testCombo()
  testAbbr()
  testRedraw()
main()
'''based on P725 [[python cookbook]]
I hope this helps me understand the classic generator algorithms 
'''