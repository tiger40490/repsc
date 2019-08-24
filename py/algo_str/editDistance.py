'''
Between the 2 solutions, topDown is easier to remember. From topDown, I can write bottomUp

Note when aa[-1]==bb[-1], it's harmless to also look at 1+topDown(a,bb), then get the minimum. The extra cost has no O() impact. It took me a lot of thinking to convince myself there's no need to compute minimum. The thinking time is a killer in speed coding.
'''
import sys
from pprint import pprint
def bottomUp(aa, bb):
  sz1,sz2=len(aa),len(bb); assert sz1<=sz2 #easier for matrix printing
  mat=[ [999999999 for _ in range(1+sz2)] for _ in range(1+sz1) ]
  
  for R in xrange(1+sz1):  #R is aa's left substring length, and 
    for C in xrange(1+sz2):#.. aa[R-1] = the substring's last char
      if R*C==0: mat[R][C]=max(R,C); continue
      r=R-1; c=C-1
      diag=mat[r][c]
      if aa[r] == bb[c]: 
        mat[R][C] = diag 
        assert diag - mat[r][C] < 2, 'adjacent values in matrix never differ by 2 or more'
        assert diag - mat[R][c] < 2, 'adjacent values in matrix never differ by 2 or more'
      else : # aa[r] != bb[c]: #exactly 3 ways: 
#1)replace aa[r] with bb[c] 2)delete aa[r] 3)append bb[c] i.e. 1+mat[R][c] 
        mat[R][C] = 1+min(diag, mat[r][C], mat[R][c])
  print '     '+'  '.join(list(bb))
  pprint(mat)
  return mat[-1][-1]
####### end of bottomUp; now topDown: 
memo=dict()
def topDown(aa,bb):
  sz1,sz2 = len(aa),len(bb) 
  if sz1*sz2 == 0: return max(sz1,sz2)
  tu=(sz1,sz2) # a tuple of (aa,bb) not needed because aa/bb never swapped, so (sz1,sz2) encodes the same info
  if tu in memo: return memo[tu]
  #print aa+' > '+bb  
  a,b = aa[:-1],bb[:-1] # truncated strings
  
  min1 = topDown(a,b)
  if aa[-1] == bb[-1]: 
    ret = min1 #2 identical asserts:
    min2 = min(topDown(a,bb), topDown(aa,b)) # for assertion only
    assert ret-min2 < 2
    assert ret == min(min1, 1+min2)
  else: ret = 1 + min(min1, topDown(a,bb), topDown(aa,b)) 
  
  memo[tu]=ret
  print aa+' > '+bb, ret
  return ret
def compare(aa,bb): #non-recursive
  if len(aa) > len(bb): tmp=aa;aa=bb;bb=tmp #for printing convenience only
  td=topDown(aa,bb); assert len(memo)==len(aa)*len(bb); memo.clear()
  assert td == bottomUp(aa,bb)
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