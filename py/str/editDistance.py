'''
showcase 
'''
from pprint import pprint

def a(mat, r, c):
  if r<0 or c<0: return 0
  return mat[r][c]

def solve(aa, bb): # find distance between aa and bb
  if len(aa) > len(bb):
    tmp=aa
    aa=bb
    bb=tmp
  sz1=len(aa)
  sz2=len(bb)
  assert sz1 <= sz2  
  mat=[ [0 for j in range(sz2)] for _ in range(sz1) ]
  # pprint(mat)
  for r in xrange(sz1):
    for c in xrange(sz2):
      print 'comparing', aa[r], bb[c]
      diag=a(mat, r-1, c-1)
      if aa[r] == bb[c]:
        mat[r][c] = diag
        continue
      mat[r][c] = 1+min(diag, a(mat,r-1,c), a(mat,r,c-1))
  # end of loop
  pprint(mat)
  return mat[-1][-1]
  
def main():
  solve('yixin', 'yiting')
main()
'''
'''