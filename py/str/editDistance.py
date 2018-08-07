'''
todo: first row numbers are too low. Perhaps extract the min() as read function?
showcase 
'''
from pprint import pprint

def read(mat, r, c):
  if r<0 or c<0: return 999
  return mat[r][c]

def solve(aa, bb): # find distance between aa and bb
  if len(aa) > len(bb):
    tmp=aa
    aa=bb
    bb=tmp
  sz1=len(aa)
  sz2=len(bb)
  assert sz1 <= sz2  
  mat=[ [0 for _ in range(sz2)] for _ in range(sz1) ]
  # pprint(mat)
  for r in xrange(sz1):
    for c in xrange(sz2):
      if r==0 and c==0: 
        mat[r][c]= 0 if aa[r] == bb[c] else 1
        continue
      diag=read(mat, r-1, c-1)
      if aa[r] == bb[c]:
        mat[r][c] = diag
      else:
        mat[r][c] = 1+min(diag, read(mat,r-1,c), read(mat,r,c-1))
      print 'comparing', aa[r], bb[c], '.. set to', mat[r][c]
  # end of loop
  pprint(mat)
  return mat[-1][-1]
  
def main():
  solve('yixin', 'yiting')
main()
'''
'''