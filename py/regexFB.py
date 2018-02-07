"""
Q: A simple regex (SRE) can use alphanumerics, dot and star. It is enclosed between implicit ^ and $. 
Write a match() function taking a SRE and a word. No white space allowed.

Detailed requirements https://wp.me/p74oew-32
"""
def match(haystack, regex):
      print   'regex = ', regex, '   haystack = ', haystack
      if 0==len(regex): return 0==len(haystack)
      c,d = (regex[0],'') if len(regex)==1 else regex[0:2]
      assert c != '*', "regex first char is star -- illegal"

      if d != '*' :
          if len(haystack) == 0: return False  
          if c!= '.' and c!= haystack[0]: return False
          return match(haystack[1:], regex[1:])
      
      if c != '.' : # literal-star. Example: Q* eating up none to all leading Q's, if any
         if 0==len(haystack): return match(haystack, regex[2:])
         print '   v v v v v   starting * loop with haystack %s vs %s' %(haystack, regex)
         i = 0
         while haystack[i] == c:
           print 'trying in * loop with i = ', i
           if match(haystack[i:], regex[2:]): 
              if len(haystack): print '  ^^^^^ ending * loop ^^^ good haystack %s vs %s' %(haystack[i:], regex[2:])
              return True
           i+=1 
         print '      ^^^^^ ending * loop ^^^  bad'
         return False
                         
      assert c == '.' and d == '*' # dot-star requires iteration over haystack
      print '   v v v v v   starting  .* loop with haystack %s vs %s' %(haystack, regex)
      for i in [0]+range(1,len(haystack)): # 0 to len-1 but never empty loop
          print 'in loop, trying i = ', i
          if match(haystack[i:], regex[2:]) :
              if len(haystack): print '  ^^^^^ ending .* loop ^^^ good haystack %s vs %s' %(haystack[i:], regex[2:])
              return True
      print '      ^^^^^ ending .* loop ^^^  bad'
      return False
 
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
