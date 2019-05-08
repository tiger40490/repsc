'''
todo: get rid of the if r==0
todo: init matrix to 1?
todo: more tests
todo: add a bottom up, non-recursive solution

showcase one-liner to clear a dict
showcase one-liner to assign two vars

Note for empty string e, e[:-1] is itself
'''
from pprint import pprint
memo = dict(); SEP = ' ^^^ '
def td(NN, HH): #top-down DP with memoization
  sz1,sz2 = len(NN),len(HH);  tu=(sz1,sz2)
  if tu in memo: return memo[tu]
  
  print NN + '>' + HH
  if   sz1 == sz2: ret = (1 if NN==HH else 0)
  elif sz1 == 0:   ret = 1 # optional (minor) optimization
 #elif sz1 >  sz2: ret = 0 # this check was moved into solve().. should not stay in this "hot" function
  else:
    assert sz1 < sz2
    ret = td(NN, HH[:-1]) # these hiding places don't include haystack's last char
    if NN[-1:]==HH[-1:] : ret += td(NN[:-1] , HH[:-1]) 
  memo[(sz1,sz2)] = ret
  return ret
def bottomUp(NN,HH):
  sz1,sz2 = len(NN),len(HH);
  mat = [[ 1 for _ in xrange(1+sz2) ] for _ in xrange(1+sz1) ]
  for r in xrange(1+sz1):
    mat[r][r] = (1 if NN[:r]==HH[:r] else 0)
    for c in xrange(r+1, 1+sz2):
      if r==0: mat[r][c] = 1; continue
      print r,c
      cnt = mat[r][c-1]
      if NN[r-1]==HH[c-1]:
        cnt += mat[r-1][c-1]
      mat[r][c]=cnt
  pprint(mat)
  return mat[-1][-1]
def solve(needle, haystack):
  haystack = haystack.replace(' ',''); assert len(needle) <= len(haystack), "invalid input"
  retB = bottomUp(needle, haystack)
  retT = td(needle, haystack); memo.clear(); 
  assert retB==retT; print SEP,retT,SEP; return retT
assert 6+5+3==solve('as', 'as ass asss')
assert 6==solve('11', '1111')
assert 4==solve('Gks', 'Geeks For Geeks')
# def packed(haystack):  return ''.join(haystack.split()) # less efficient than replace()
'''Req:
Given longer and short strings Haystack vs Needle, can string-N match a sub-sequence (not necessarily substring) of string-H? You can say we are checking if string-N is hiding in string-H. If yes how many hiding places (or sub-sequences) can you find? 

For example, if length of string-N is 3, then each hiding place is a tuple of 3 subscripts into string-H, where the 3 characters would form a string equal to string-N

Eg: H = GeeksForGeeks; N = Gks. Answer is 4 subsequences i.e. 4 hiding places
'''