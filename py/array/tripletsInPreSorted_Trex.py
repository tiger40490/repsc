'''
todo: save the pairs in a dict!

Same cost in both solutions, but I feel sol3 is more clever
'''
li=sorted([12,3,6,2,4,20,15,8,10,9,1,5])
li=sorted([1,2,4,8,16,32,64,128,256,512,1024,2048])
sz=len(li)
pairs=[]

def sol3loop(): 
  cost=0; cnt=0
  for s in range(sz-1):
    for b in range(s+1, sz):
      sm,bi = li[s],li[b]
      if bi%sm: continue
      newPair = (sm,bi)
      for _sm,_bi in pairs:
        cost += 1
        if sm == _bi: cnt+=1; print 'match -', _sm,_bi,bi
      pairs.append(newPair)
      #print newPair
  print 'cost =', cost, ', cnt =', cnt

def sol2(): # based on Shanyou's input
  cost=0; cnt=0
  for s in range(sz-1):
    for b in range(s+1, sz):
      sm,bi = li[s],li[b]
      if bi%sm == 0: 
        pairs.append((sm,bi))
  for i in xrange(len(pairs)):
    sm, bi = pairs[i]
    for j in xrange(i+1, len(pairs)):
      sm2, bi2 = pairs[j]
      cost += 1
      if bi == sm2: cnt+=1; print 'match -', sm,bi,bi2
  print 'cost =', cost, ', cnt =', cnt
def main():
  sol3loop()
  #sol2()
main()
'''Requirement: https://bintanvictor.wordpress.com/2018/03/03/find-triplet-x-divide-y-y-divides-z/
'''
