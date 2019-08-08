'''
todo: more tests

Assuming sz = len(vec)
vec[ -1] == vec[ sz-1] is the #1 char from end
vec[:-2] == vec[:sz-2] is a clone after chopping last 2 chars
Note for empty string e, e[:-1] is itself

showcase using read() to implement conditional logic. Alternative is if/continue within the loop.. confusing
showcase using an invalid value (0 is valid) to mark the unused region of matrix. See blogpost
showcase one-liner to clear a dict
showcase one-liner to assign two vars
'''
memo = dict(); SEP = ' ^^^ '
def topdn(NN, HH): #top-down DP with memoization
  sz1,sz2 = len(NN),len(HH);  tu=(sz1,sz2)
  if tu in memo: return memo[tu]
  
  if   sz1 == sz2: ret = (1 if NN==HH else 0)
  elif sz1 == 0:   ret = 1 # optional optimization but meaningful
  
 #elif sz1 >  sz2: ret = 0 # Important simplification : this check was moved into solve().. should not stay in this "hot" function
  else:
    assert sz1 < sz2
    ret = topdn(NN, HH[:-1]) # these hiding places don't include haystack's last char
    if NN[-1:]==HH[-1:] : ret += topdn(NN[:-1] , HH[:-1]) 
  memo[(sz1,sz2)] = ret
  print NN + ' > ' + HH + ' ..', ret
  return ret
### end of topDown; rest is bottom up:
mat = list()
def pprint():
  for r in xrange(len(mat)):
    for c in xrange(len(mat[0])): print '%2s' % read(r,c),
    print
def read(r,c): # $$Valuable reusable technique
  if r > c: return 0
  if r==0: return 1 #special logic
  return mat[r][c]
def botup(NN,HH): #based on the more natural topdn, this botup algo is unreadable
  sz1,sz2 = len(NN),len(HH);
  global mat; mat=[[999999 for _ in xrange(1+sz2)]for _ in xrange(1+sz1) ]

  #r:=len(NN left part), so loop from r=1 till sz1
  for r in xrange(1, 1+sz1): 
    for c in xrange(r, 1+sz2):
      mat[r][c] = read(r,c-1)
      if NN[r-1]==HH[c-1]:
        mat[r][c] += read(r-1,c-1)
  print '    '+'  '.join(list(HH))      
  pprint()
  return read(-1,-1)
def solve(needle, haystack):
  haystack = haystack.replace(' ',''); assert len(needle) <= len(haystack), "invalid input"
  retT = topdn(needle, haystack); memo.clear(); 
  retB = botup(needle, haystack)
  assert retB==retT; print SEP,retT,SEP; return retT
  
assert 6+5+3==solve('as', '0 as ass asss')
assert 6==solve('aa', 'babbabaa')
assert 4==solve('Gks', 'Geeks For Geeks')
assert 0==solve('aaaa', 'bababa')
assert 0==solve('a', 'b')
assert 1==solve('a', 'ab')
assert 1==solve('a', 'ba')
# def packed(haystack):  return ''.join(haystack.split()) # less efficient than replace()
'''Req: Rahul's Uber onsite question.
Given longer and short strings Haystack vs Needle, can string-N match a sub-sequence (not necessarily substring) of string-H? You can say we are checking if string-N is hiding in string-H. If yes how many hiding places (or sub-sequences) can you find? 

For example, if length of string-N is 3, then each hiding place is a tuple of 3 subscripts into string-H, where the 3 characters would form a string equal to string-N

Eg: H = GeeksForGeeks; N = Gks. Answer is 4 subsequences i.e. 4 hiding places
'''
