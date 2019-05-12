'''
todo: understand why
todo: what if the pool has dupes?

'''
def _com(func, items, n): #internal recursive generator function
  if n==0: yield [] # recursion end
  else:
    for i,val in enumerate(items):
      listLedByVal = [val]
      for newList in _com(func, func(items,i), n-1): #recurse down
        yield listLedByVal + newList #concat 2 lists
def combo(pool, n):
  def after_i_th_item(pool,i):
    return pool[i+1:]
  return _com(after_i_th_item, pool,n)
def subsetPerm(pool, n): #accepts distinct items
  def skip_i_th_Item(pool, i):
    return pool[:i] + pool[i+1:]
  return _com(skip_i_th_Item, pool, n)# returns generator object, to be used in iteration context
  
def testCombo():
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
main()
'''based on P725 [[python cookbook]]
I hope this helps me understand the classic generator algorithms 
'''