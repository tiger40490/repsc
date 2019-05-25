def _com(func, pool, n):
  if n == 0: yield []; return
  for pos,val in enumerate(pool):
    for newList in _com(func, func(pool,pos), n-1):
      yield [val] + newList
def perm(pool, n):
  def skip_me(pool, pos):
    return pool[:pos] + pool[pos+1:]
  return _com(skip_me, pool, n)

cnt = 0
for artefact in perm(list('abc'),2): 
  print artefact
  cnt += 1
print cnt

'''periodically, i rewrite part of the cookbook to refresh memory and exercise the memory "muscle"
'''