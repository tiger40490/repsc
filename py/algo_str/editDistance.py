'''
todo: topDown(aa,b) and topDown(b,aa) looks like a bug
ret = topDown(a,b) ?? should compare with the other options
todo: is the sz1 < sz2 necessary in each algo?

todo: add tests and simplify

I always designate the shorter string as aa and longer as bb. Is it necessary? Not sure, but it simplifies my thinking
'''
import sys
from pprint import pprint
def read(mat, r, c):
  if r<0 or c<0: return 88
  return mat[r][c]
def bottomUp(aa, bb): # find distance between aa and bb
  sz1=len(aa); sz2=len(bb); assert sz1 <= sz2  
  mat=[ [0 for _ in range(sz2)] for _ in range(sz1) ]
  for r in xrange(sz1):
    for c in xrange(sz2):
      if r==0 and c==0: 
        mat[0][0]= 0 if aa[0] == bb[0] else 1; continue
      diag=read(mat, r-1, c-1)
      if aa[r] != bb[c]: #exactly 3 ways: 
#1)replace aa[r] with bb[c] 2)delete aa[r] 3)append bb[c] i.e. 1+mat[r,c-1] 
        mat[r][c] = 1+min(diag, read(mat,r-1,c), read(mat,r,c-1))
      else: 
        mat[r][c] = diag
      #print 'comparing', aa[r], bb[c], '.. set to', mat[r][c]
  pprint(mat)
  return mat[-1][-1]
####### end of bottomUp; now topDown: 
memo=dict()
def topDown(aa,bb):
  sz1    , sz2 = len(aa),len(bb) 
  if sz1 > sz2: return 9999999999999 #infinity
  if sz1 == 0: return sz2
  tu=(sz1,sz2) # (aa,bb) not needed because aa/bb never swapped 
  if tu in memo: return memo[tu]
  print aa+' > '+bb  
  a=aa[:-1]; b=bb[:-1]
  if aa[-1] == bb[-1]: ret = topDown(a,b) #? why no need to compare?
  else: ret=1+min(topDown(a,b), topDown(a,bb),  
                  topDown(aa,b), topDown(b,aa)) #aa/b relative lengths..either way
  memo[tu]=ret
  return ret
  
def compare(aa,bb): #non-recursive
  if len(aa) > len(bb): tmp=aa;aa=bb;bb=tmp
  #memo.clear(); td=topDown(aa,bb)
  #assert     td == bottomUp(aa,bb)
  #return td
  return bottomUp(aa,bb)
assert 1==compare('i', 'ai')
assert 1==compare('islander', 'slander')
assert 2==compare('yixin', 'yiting')
assert 1==compare('geek', 'gesek')
assert 3==compare('Sunday', 'Saturday')
assert 1==compare('cat', 'cut')
assert 3==compare('tape', 'hat')
assert 6==compare("abcdefg", "xabxcdxxefxgx")
assert 3==compare("example", "samples") 
assert 6==compare("sturgeon", "urgently")
assert 6==compare("levenshtein", "frankenstein")
assert 5==compare("distance", "difference")
'''
Req: given strings (shorter) aa and bb (longer), how many transformations from aa to bb? Return the minimum steps or "edits"?
'''