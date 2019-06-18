'''
Q: what if the pool contains duplicates? Very common in REALISTIC abbr problems.
A: if performance not too serious (data size not extreme), then (Perhaps simplest solution) just treat the pool as non-repeating and then uses a dictionary. In reality, we don't get horrible input like 010100000001010010. No point spending so much time optimizing an algo that's not really needed in any imaginable context.
A: if performance becomes a real problem, then need to try other algorithms, based on the specific context

Efficiency? May not be optimal due to recursion, but still elegant

sound-byte: Note each nested function always returns a list

challenge: _yield is hard to test without a high-order function

Note with non-repeating pool, "fixed-size abbr" and "combo" algos are identical

Most useful: combo/abbr, subsetPerm. The redraw* algos are often used in coding tests too.
'''
from pprint import pprint
import sys
def _yield(func, pool, howManyMore, logLevel=0): 
  '''internal recursive generator function to generate all subsets of pool, each in a list of length = howManyMore
* sound-byte: _yield() calls itself from inside a loop
* sound-byte: _yield() generates a bunch of lists
* sound-byte: for newList in _yield(..)
* sound-byte:   func,func(...)
* sound-byte: pos is needed only once

The tricky part of _yield() is really one line only. Hard to understand; hard to memorize...
  '''
  if howManyMore==0: yield []; return #recursion exit condition
  assert howManyMore > 0
  indent = (3-howManyMore)*'  '
  
  ## 'char' is one type of "value" but a concrete type
  for pos,char in enumerate(pool):
    if logLevel: print indent, 'listLedByVal =', char
      
    ## func is a two-arg callable that returns a subset
    for newList in _yield(func, func(pool,pos), howManyMore-1, logLevel): #recurse down
      if logLevel: print indent, [char] + newList
      yield [char] + newList

def abbr(word, n): #generates all abbreviations of length==n. 
# if pool size==55, then 55-C-n abbreviations??
  def after_i_th_item(pool,pos):
    return pool[pos+1:]
  return _yield(after_i_th_item, word,n) #,True)
def allAbbr(word):
  import itertools
  gen = itertools.chain()
 #for n in xrange(1+len(word)):
  for n in range(len(word),0,-1)+[0]: #longest first
    gen = itertools.chain(gen, abbr(word,n))
  return gen
def redrawP(pool, n): # permutations by n redraws from same pool. 
# If pool size==55, then 55^n outcomes
  def keepAll(pool, unused): 
    return pool
  return _yield(keepAll, pool, n) #, True)
def redrawC(pool, n): # generate combos by n redraws from same pool. See my notes in the txt file.
  def keepAllFollower(pool,pos): 
    return pool[pos:]
  return _yield(keepAllFollower, pool, n) #, True)
def subsetPerm(pool, n): #accepts distinct items
  def skip_i_th_Item(pool, pos):
    return pool[:pos] + pool[pos+1:]
  return _yield(skip_i_th_Item, pool, n)#, True)# returns generator object, to be used in iteration context
def testRedraw():
  print '  v v  --  redraw combinations  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abc'
  for artifact in redrawC(nonRepeat, 3):
    word = ''.join(artifact)
    fmt2 += word + ' '
    fmt1 += str(artifact)
    cnt += 1
    unique[word]=1
  print fmt2, fmt1
  assert len(unique)==10==cnt

  print '  v v  --  redraw permutations  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abc'
  
  outputLen=2
  for artifact in redrawP(nonRepeat, outputLen):
    word = ''.join(artifact)
    fmt2 += word + ' '
    fmt1 += str(artifact)
    cnt += 1
    unique[word]=1
  print fmt2, fmt1
  assert len(unique)==len(nonRepeat)**outputLen==cnt
def testAbbr():
  print '  v v  --  abbr  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abcd'
  for artifact in allAbbr(nonRepeat): #, 3):
    word = ''.join(artifact)
    fmt2 += word + '; '
    fmt1 += str(artifact)
    cnt += 1
    unique[word]=1
  print fmt2 #, fmt1
  assert len(unique)==2**len(nonRepeat)==cnt
def testCombo():
  print '  v v  --  combo  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat=[1,2,3,4,5,6,7]
  for artifact in abbr(nonRepeat, 3):
    word = ''.join(str(i) for i in artifact)
    fmt2 += word + ' '
    fmt1 += str(artifact)
    cnt += 1
    unique[word]=1
  print fmt2
  assert len(unique)==7*6*5/3/2==cnt
def testPerm():
  print '  v v  --  subsetPerm  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abcd'
  outputLen=2
  for artifact in subsetPerm(nonRepeat, outputLen):
    word = ''.join(artifact)
    fmt2 += word + ' '
    fmt1 += str(artifact)
    cnt += 1
    unique[word]=1
  print fmt2, fmt1
  
  poolSz=len(nonRepeat); 
  expected=1
  for i in xrange(outputLen): 
    expected *= poolSz-i
  assert len(unique)==expected==cnt
  
  print '  v v  --  full Permutations  --  v v'
  li=list(subsetPerm(nonRepeat, len(nonRepeat))) #full permutation
  unique=dict(enumerate(li))
  for perm in li: print ''.join(perm),
  print
  
  expected=1
  for i in xrange(poolSz): 
     expected *= poolSz-i
  assert len(unique)==expected==len(li)
def main():
  testPerm()
  testCombo()
  testAbbr()
  testRedraw()
main()
'''based on P725 [[python cookbook]]
I hope this helps me understand the classic generator algorithms 
'''