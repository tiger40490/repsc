def sol3loop(input): 
  li=sorted(input); sz=len(li)
  factorsOf=dict() # key is a big number, value is its factors as a list
  cost=0; cnt=0
  for s in range(sz-1):
    for b in range(s+1, sz):
      sm,bi = li[s],li[b]
      if bi%sm: continue
      for factor in factorsOf.get(sm, []):
        cnt+=1; print 'match -', factor,sm,bi
      if bi in factorsOf:
        factorsOf[bi].append(sm);
      else:
        factorsOf[bi]=[sm]
  return cnt
  
def main():
  # any 3 numbers would form a triplet, so cnt = 12-C-3 = 220
  assert(220 == sol3loop([1,2,4,8,16,32,64,128,256,512,1024,2048]))
main()
'''Requirement: https://bintanvictor.wordpress.com/2018/03/03/find-triplet-x-divide-y-y-divides-z/
'''
