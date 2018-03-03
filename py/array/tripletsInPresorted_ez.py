li=sorted([12,3,6,2,4,20,15,8,10,9,1,5])
sz=len(li)
pairs=[]

def main():
  for s in range(sz-1):
    for b in range(s+1, sz):
      sm,bi = li[s],li[b]
      if bi%sm: continue
      newPair = (sm,bi)
      for _sm,_bi in pairs:
        if sm == _bi: print 'match -', _sm,_bi,bi
      pairs.append(newPair)
      print newPair
main()
'''Requirement: 
'''
