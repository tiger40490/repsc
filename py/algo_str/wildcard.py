'''
todo: botup

showcase: standalone decorator applied on an instance method
showcase: str.count(char)
Passed all 1809 Leetcode test cases. 
'''
import sys
from functools import wraps
def compact(raw): #returns a compact form
  if len(raw) < 999: return raw  #compact() is slow on small strings
  raw = raw.replace(' ','')+' ' #space as terminator
  if raw == '': return raw
  vec=[]
  repeat=1
  for i,ch in enumerate(raw):
    if i==0: continue #tolerable code smell
    if     raw[i-1] == ch: repeat += 1; continue
    assert raw[i-1] != ch
    vec.extend( [raw[i-1], repeat] )
    repeat = 1
  ret = ''.join(str(it) for it in vec)
  return ret
memo=dict()
def memoDecorator(f):
   @wraps(f)
   def wrapper(*args):
     key = compact('/'.join(args[1:]))
     if key in memo: 
       #print ':) memoization hit'
       return memo[key]
     memo[key] = ret = f(*args) # speeds up first test
     return ret
   return wrapper
class Solution(object):   
 @memoDecorator
 def isMatch(self, s, p):
   assert ' ' not in s+p, 'space disallowed'
   haystack = s; regex=p.replace('**' , '*')
   #print 'haystack = ', haystack, '\t regex = ', regex
   if len(regex) - regex.count('*') > len(haystack): return False #minor optimization
   if regex == '': return '' == haystack
   if haystack == '': return '' == regex.replace('*','')
   #### trivial cases done
   c=regex[0]; a=haystack[0]
   if c=='?': return          self.isMatch(haystack[1:], regex[1:])
   if c!='*': return c==a and self.isMatch(haystack[1:], regex[1:])
   assert c=='*'
   if regex[-1] != '*': #always prefer to avoid this loop
     return self.isMatch(haystack[::-1], regex[::-1]) #reverse str ?
    
   sz=len(haystack)
   #print '-- starting * loop --'
   for i in range(sz+1):
     newhay = haystack[sz-i:sz] #could be empty
     assert len(newhay) == i
     if self.isMatch(newhay, regex[1:]): return True
   return False
   
assert Solution().isMatch('aaaaa', '*aaaaa*')
assert Solution().isMatch('ab', 'a*')
assert Solution().isMatch('ab', '*b')
assert Solution().isMatch('ab', '*')
assert Solution().isMatch('ab', '*?')
assert Solution().isMatch('ab', '*?')
assert Solution().isMatch('ab', '*?*')
assert Solution().isMatch('ab', '??')
assert Solution().isMatch('ab', '?') == False
assert Solution().isMatch("aabbbbaababbabababaabbbbabbabbaabbbabbbabaabbaaaababababbababbabbbbabaaabaaabaabbaaaabbbbabaaabbbbbabbbaabbbbbabaabababaaabaaababaababbaaabaabbabaababbabababaaababbabbabaabbbbabbbbabaabbaababaaabababbab", "a*b*a*b*aaaa*abaaa**b*a***b*a*bb****ba*ba*b******a********a**baba*ab***a***bbba*b**a*b*ba*a*aaaa*ab**") == False

assert Solution().isMatch("abbbabaaabbabbabbabaabbbaabaaaabbbabaaabbbbbaaababbb","**a*b*aa***b***bbb*ba*a") == False
assert Solution().isMatch("ababaabaabbbbbabbbaaababbaabbbbbaaabaabababaaaabbabbbbabbaaaaaaaaabaababbaabaaababaababaabbabbbbbabababbabaabbbaababbbababaaabbbbbbbbbabaababaaabababbbbabbaabaaabbbababbbbbbbbabaaaabbabbbbabbaaabbbbababab", "ab**bbb*a*ab*bb*aa*a***ab*b**b***bba****b*aaabaa**bb*ab*a***abb****bb*a**b*****a*abaa**a****aab**aa**bbb") == False
assert Solution().isMatch('adceb', '*a*b')

'''Req: https://bintanvictor.wordpress.com/wp-admin/post.php?post=32822&action=edit
'''