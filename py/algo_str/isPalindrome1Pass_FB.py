def check(a):
  last = len(a)-1
  le = 0; ri = last
  
  while True:
    # now le and/or ri are untested
    if ri <= le: return True # I hope to have only one check for this condition.
    #print 'checking le =', le
    if not a[le].isalnum():
      if le <= last-1: 
        le += 1; 
        continue # Aha!
      return True
    #print 'checking ri =', ri
    if not a[ri].isalnum():
      if 1<=ri : ri -= 1; continue
      return True
      
    if a[le].lower() != a[ri].lower(): return False
    le += 1
    ri -= 1
    
assert(check("A man, a plan, a canal: Panama") )  
assert(check(' a'))
assert(check(' aa'))
assert(check('z '))
assert(check('zz '))
assert(check(' c '))
assert(check('  c '))
assert(not check(' cd '))
assert(not check(' c  d '))
assert(not check(' cd d '))

'''Q:
Given a sentence as a string, check if it's a palindrome. Challenge is the "unwanted" characters like space and punctuations.

I said the clean solution would be two-pass
1) remove all unwanted characters 
2) pass the clean string to a simple utility funciton 

Both steps are easy to implement, but space complexity is O(N). Interviewer wanted a more space-efficient solution, so I said I would have to do one scan with two opposing pointers.
'''