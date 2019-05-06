'''
todo: more tests
todo: bottom up solution

showcase one-liner function
showcase one-liner to remove spaces
showcase one-liner to clear a dict
showcase one-liner to assign two vars

Note for empty string e, e[:-1] is itself
'''
memo = dict(); SEP = ' ^^^ '
def td(NN, HH): #top-down DP with memoization
  sz1,sz2 = len(NN),len(HH);  tu=(sz1,sz2)
  if tu in memo: return memo[tu]
  
  print NN + '>' + HH
  if   sz1 == sz2: ret = (1 if NN==HH else 0) #most likely scenario first 
  elif sz1 == 0:   ret = 1 # minor optimization
 #elif sz1 >  sz2: ret = 0 # this check was moved into solve().. should not stay in this "hot" function
  else:
    assert sz1 < sz2
    ret = td(NN, HH[:-1]) 
    if NN[-1:] == HH[-1:] :  ret += td(NN[:-1], HH[:-1])
  memo[(sz1,sz2)] = ret
  return ret
def packed(haystack):  return ''.join(haystack.split()) # can inline if used only once 
def solve(needle, haystack):
  haystack = packed(haystack); assert len(needle) <= len(haystack), "invalid input"
  memo.clear()
  ret = td(needle, haystack); print SEP,ret,SEP; return ret
assert 6+5+3==solve('as', 'as ass asss')
assert 6==solve('11', '1111')
assert 4==solve('Gks', 'Geeks For Geeks')
'''Req:
Given longer and short strings Haystack vs Needle, can string-N match a sub-sequence (not necessarily substring) of string-H? You can say we are checking if string-N is hiding in string-H. If yes how many hiding places (or sub-sequences) can you find? 

For example, if length of string-N is 3, then each hiding place is a tuple of 3 subscripts into string-H, where the 3 characters would form a string equal to string-N

Eg: H = GeeksForGeeks; N = Gks. Answer is 4 subsequences i.e. 4 hiding places
'''