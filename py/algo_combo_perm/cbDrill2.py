def gen(func, pool, n):
  if n==0: yield []; return
  for pos, ch in enumerate(pool):
    for newList in gen(func, func(pool, pos), n-1):
      yield [ch] + newList
def combo(pool, n):
  def after(pool, pos):
    return pool[pos+1:]
  return gen(after, pool, n)

cnt = 0
for artifact in combo(list('abcde'),2):
  print artifact
  cnt += 1
print cnt