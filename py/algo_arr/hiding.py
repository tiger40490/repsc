'''todo: if n is 0 length?
'''
di = dict()
def td(needle, haystack): #top-down DP with memoization
  sz1, sz2 = len(needle), len(haystack)
  tu = (sz1,sz2)
  if tu in di: return di[tu]
  
  print needle + '>' + haystack
  #if sz1 == 0: return 1??
  if   sz1 >  sz2: ret = 0
  elif sz1 == sz2: ret = (1 if needle == haystack else 0)
  else:
    ret = td(needle, haystack[:-1]) 
    if needle[-1:] == haystack[-1:]:
      ret += td(needle[:-1], haystack[:-1])
  di[(sz1,sz2)] = ret
  return ret

def solve(needle, haystack):
  print td(needle, haystack), 'hiding places'

solve('Gks', 'GeeksForGeeks')
'''Req:
Given longer and short strings Haystack vs Needle, can string-N match a sub-sequence (not necessarily substring) of string-H? You can say we are checking if string-N is hiding in string-H. If yes how many hiding places or sub-sequences can you find? 

For example, if length of string-N is 3, then each hiding place is a tuple of 3 subscripts into string-H...

Eg: H = GeeksForGeeks; N = Gks. Answer is 4 subsequences i.e. 4 hiding places
'''