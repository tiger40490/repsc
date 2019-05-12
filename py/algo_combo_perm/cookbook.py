'''
todo: understand why
todo: add abbreviation
todo: what if the pool has dupes?
'''
def _com(func, items, n, logLevel=0): #internal recursive generator function
  # n == how many additional items wanted
  if n==0: yield [] # recursion end
  else:
    indent = (3-n)*'  '
    for i,val in enumerate(items):
      listLedByVal = [val]
      if logLevel: print indent, 'listLedByVal =',val
      
      # func is a func that returns a subset
      for newList in _com(func, func(items,i), n-1, logLevel): #recurse down
        if logLevel: print indent, listLedByVal + newList
        yield listLedByVal + newList #concat 2 lists
def redraw(pool, n): # redraw n times from same pool. If pool size=55, then 55^n outcomes
  def keepAll(pool,i): return pool
  return _com(keepAll, pool, n, True)
def combo(pool, n):
  def after_i_th_item(pool,i):
    return pool[i+1:]
  return _com(after_i_th_item, pool,n)#,True)
def subsetPerm(pool, n): #accepts distinct items
  def skip_i_th_Item(pool, i):
    return pool[:i] + pool[i+1:]
  return _com(skip_i_th_Item, pool, n)# returns generator object, to be used in iteration context
  
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
  assert len(unique)==9==cnt
def testCombo():
  print '  v v  --  combo  --  v v'
  fmt1, fmt2='', ''; cnt=0; unique=dict()
  nonRepeat='abcd'
  for out in combo(nonRepeat, 2):
    word = ''.join(out)
    fmt2 += word + ' '
    fmt1 += str(out)
    cnt += 1
    unique[word]=1
  print fmt2, fmt1
  assert len(unique)==6==cnt
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
  testRedraw()
main()
'''based on P725 [[python cookbook]]
I hope this helps me understand the classic generator algorithms 
'''