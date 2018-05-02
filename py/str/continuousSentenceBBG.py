import bisect

input = ('al', 'ali', 'alice', 'bob', 'dan')
hay = sorted(input)
engDict = set(input) # the English dictionary
matched=list() # list of words parsed

def myReturn(pw): # to reduce indentation levels
  global matched
  matched.insert(0, pw)  
  return True

def parse(remain):
  sz = len(remain)
  if sz == 0: return True # entire sentence parsed :)
  if remain in engDict: return myReturn(remain)
  for i in range(1,sz+1):
    pw = remain[0:i] # possible word. remain[0:n] would return the first n characters from "remain".
    print 'trying', pw
    if pw in engDict:    
      if parse(remain[i:]): return myReturn(pw)
      
    # The else block below is not needed to solve the problem. It's added purely for efficiency.
    else: # is pw a possible prefix? Locate the nearest 2 neighbours
      tmp = bisect.bisect_left(hay, pw)
      le = hay[tmp-1] if tmp>=1 else '/'
      tmp = bisect.bisect_right(hay, pw)
      ri = hay[tmp]   if tmp<len(engDict) else '\\'
      print pw, 'not in engDict. left/right are: ', le, ri 
      if not   (le.startswith(pw) or ri.startswith(pw)):
        print pw, 'is not a prefix of any word.. giving up on', remain
        return False;
  # end of for loop    
  return False      
def main():
  result = parse('alicealx')
  print result, (matched if result else '')
main()
'''I think this is a classic algo question
Given a English dictionary of words (no numbers no underscores) and a long sentence. Someone has removed all the spaces. Now restore it by adding the spaces. If there's no way to parse the sentence just return False, otherwise return True. 
'''
