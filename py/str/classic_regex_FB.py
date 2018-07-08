# Focus on correctness. The performance requirements are rarely needed so let's not spend too much time
def match(haystack, regex):
      print 'haystack = ', haystack, '\t regex = ', regex
      if 0==len(regex): return 0==len(haystack)
      c,d = (regex[0],'') if len(regex)==1 else regex[0:2]
      assert c != '*', "regex first char is star -- illegal"

      if d != '*' :
          if len(haystack) == 0: return False  
          if c!= '.' and c!= haystack[0]: return False
          return match(haystack[1:], regex[1:])
          
      assert d == '*'
      
      # now deal with the right end as an optimization
      z = regex[-1]
      if z != '*' and z != '.' :
        return len(haystack)>0 and haystack[-1] == z and match(haystack[:-1], regex[:-1])
      
      ##################3
      if c != '.' : # literal-star. Example: Q* eating up none to all leading Q's, if any
         if 0==len(haystack): return match('', regex[2:])
         print '   v v v v v   starting * loop with haystack %s vs %s' %(haystack, regex)
         
         # first try skipping the literal-star, as this is a shorter recursion stack
         if match(haystack, regex[2:]): return True
         
         while haystack[0] == c:
           haystack = haystack[1:]
           print 'trying in * loop'
           if match(haystack, regex): # try consuming the first char in haystack
              return True 
         print '      ^^^^^ ending * loop ^^^  bad'
         return False
                         
      assert c == '.' and d == '*' # dot-star requires iteration over haystack
      print '   v v v v v   starting  .* loop with haystack %s vs %s' %(haystack, regex)
      for i in [0]+range(1,len(haystack)): # 0 to len-1 but never empty loop
          print 'in loop, trying i = ', i
          if match(haystack[i:], regex[2:]) :
              if len(haystack): print '  ^^^^^ ending .* loop ^^^ good haystack %s vs %s' %(haystack[i:], regex[2:])
              return True
          
          if len(haystack)>=i+1 and match(haystack[i+1:], regex) :
              return True
      print '      ^^^^^ ending .* loop ^^^  bad'
      return False

def main():
  #assert match("acaabbaccbbacaabbbb", "a*.*b*.*a*aa*a*") # .* need to be greedy as an optimization
  assert not match("", ".*c")
  assert match('aab', 'c*a*b')
  assert not match("aaaaaaaaaaaaaaaaab", "a*a*c")
  assert not match("ab", ".*c")
  assert match('ab', '.*')
  assert match('aa', 'a*')
  assert not match('', '.')
  assert match('xyab-abc', '.*ab.*c.*x*')
  assert match('xyab-abc', '.*ab.*c.*.*')
  assert match('xyab-abc', '.*ab.*c')
  assert match('aaaaaaab-abc', 'a*aab.*c')
  assert match('aab-abc', 'a*aab.*c')
  assert match('aabc', 'a*aab.*..*x*')
  assert not match('abc', 'a*aab.*c')
  assert match('a-aab', 'a*.*a*aab')
  assert not match('a-aab', 'a*a*aab')
main()
"""
Q: A simple regex (SRE) can use alphanumerics, dot and star. It is enclosed between implicit ^ and $. 
Write a match() function taking a SRE and a word. No white space allowed.

Detailed requirements https://wp.me/p74oew-32
"""