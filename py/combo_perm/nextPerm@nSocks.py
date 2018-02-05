'''Requirement -- given x partially missing pairs socks of various colors, 
generate all the permutations, in ascending order. Each color has an value.'''
import bisect

perm = list('kcedcb')
perm = sorted(perm)
N = len(perm)

def swap(p1, p2):
  tmp = perm[p1]
  perm[p1] = perm[p2]
  perm[p2] = tmp
  
'''find the next lowest permutation'''
def next_perm():
  print 'b4:', perm
  
  # start at 2nd last pos in current permutation
  for p2u in reversed(range(N-1)):
    if perm[p2u] < perm[p2u+1]: break
    if p2u == 0:
      print perm, 'is the highest permutation'
      return False # can return different types:)  
  print perm[p2u], 'is the letter to upgrade, at p2u =', p2u
    
  # pick the next higher char among the rest and use it in p2u
  li = sorted(perm[p2u+1:N])
  bis = bisect.bisect_right(li, perm[p2u])
  swp = p2u + len(li) - bis
  print 'swp =', swp, perm[swp]
  swap(p2u, swp)
  return perm[0:p2u+1] + sorted(perm[p2u+1:N])
  
def main():
  global perm
  changes=0;
  while(perm):
    changes += 1
    perm = next_perm()
  print 'changes =', changes
main()
