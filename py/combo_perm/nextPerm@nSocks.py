'''Requirement -- given x partially missing pairs socks of various colors, 
generate all the permutations, in ascending order. Each color has an value.'''
import bisect
perm = list('kcdcba')
N = len(perm)

def swap(p1, p2):
  tmp = perm[p1]
  perm[p1] = perm[p2]
  perm[p2] = tmp
'''find the next lowest permutation
return false when there's no more
'''
def next_perm():
  # locate the p2u i.e. position to upgrade.All left positions will stay unchanged.
  print 'current perm =', perm
  for p2u in reversed(range(N-1)):
    #print 'pos = ', p2u
    if perm[p2u] < perm[p2u+1]: break
    if p2u == 0:
      print perm, 'is the highest permutation'
      return ''
    #print perm[p2u], '>=', perm[p2u+1]
    
  #print perm[p2u], 'is the letter to upgrade'
    
  # pick the next higher char among the rest and use it in p2u
  li = sorted(perm[p2u+1:N])
  pos = bisect.bisect_right(li, perm[p2u])
  swapPos = p2u + len(li) - pos
  #print 'pos =', pos, li[pos]
  #print 'swapPos =', swapPos, perm[swapPos]
  swap(p2u, swapPos)
  
  # the right positions simply sort
  return perm[0:p2u+1] + sorted(perm[p2u+1:N])
  
  
def main():
  global perm
  while(perm):
    perm = next_perm()
  
main()
