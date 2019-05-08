'''
'''
import sys
from pprint import pprint
def bottomUp(aa, bb):
  sz1,sz2=len(aa),len(bb); assert sz1<=sz2 #easier for matrix printing
  mat=[ [0 for _ in range(1+sz2)] for _ in range(1+sz1) ]
  
  for r in xrange(1+sz1):  #r is aa's left substring length, and 
    for c in xrange(1+sz2):#.. aa[r-1] is the substring's last char
      if r*c==0: mat[r][c]=max(r,c); continue
      diag=mat[r-1][c-1]
      if aa[r-1] != bb[c-1]: #exactly 3 ways: 
#1)replace aa[r-1] with bb[c-1] 2)delete aa[r-1] 3)append bb[c-1] i.e. 1+mat[r,c-1] 
        mat[r][c] = 1+min(diag, mat[r-1][c], mat[r][c-1])
      else: # when last chars of both strings match, always better to use diag
        mat[r][c] = diag 
        assert diag - min(mat[r-1][c],mat[r][c-1]) < 2, 'adjacent values in matrix never differ by 2 or more'
  print '     '+'  '.join(list(bb))
  pprint(mat)
  return mat[-1][-1]
####### end of bottomUp; now topDown: 
memo=dict()
def topDown(aa,bb):
  sz1,sz2 = len(aa),len(bb) 
  if sz1*sz2 == 0: return max(sz1,sz2)
  tu=(sz1,sz2) # (aa,bb) not needed because aa/bb never swapped 
  if tu in memo: return memo[tu]
  #print aa+' > '+bb  
  a,b = aa[:-1],bb[:-1]
  min2 = min(topDown(a,bb), topDown(aa,b))
  
  if aa[-1] == bb[-1]: 
    ret = topDown(a,b) #3 identical asserts
    assert ret == min(topDown(a,b), 1+min2)
    assert ret <= 1+min2
    assert ret-min2 <= 1 
  else: ret = 1 + min(topDown(a,b), min2) 
  
  memo[tu]=ret
  print aa+' > '+bb, ret
  return ret
def compare(aa,bb): #non-recursive
  if len(aa) > len(bb): tmp=aa;aa=bb;bb=tmp #for printing convenience only
  td=topDown(aa,bb); print len(memo), 'mem'; memo.clear()
  assert     td == bottomUp(aa,bb)
  return td
assert 6==compare("sturgeon", "urgently")
assert 1==compare('islander', 'slander')
assert 2==compare('yixin', 'yiting')
assert 1==compare('geek', 'gesek')
assert 3==compare('Sunday', 'Saturday')
assert 1==compare('cat', 'cut')
assert 6==compare("abcdefg", "xabxcdxxefxgx")
assert 6==compare("levenshtein", "frankenstein")
assert 5==compare("distance", "difference")
assert 3==compare("example", "samples") 
assert 3==compare('tape', 'hat')
'''
Req: given strings (shorter) aa and bb (longer), how many transformations from aa to bb? Return the minimum steps or "edits"?

classic DP problem, with relatively simple bottom-up solution
'''