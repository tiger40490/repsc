import bisect
Hopeless = -99
input = ('al', 'ali', 'alice', 'bob', 'dan')
input = ["cats","dog","sand","and","cat"]

hay = sorted(input)
wordDict = hay # the English dictionary
matched=list() # list of words parsed

def myReturn(pw): # to reduce indentation levels
  global matched
  matched.insert(0, pw)  
  return True

def check1char(char):
      print 'check1char', char
      for word in wordDict:
        if char in word: 
          return True
      return False

def parse(remain): # This solution uses backtracking but inefficient
  sz = len(remain)
  if sz == 0: return True # entire sentence parsed :)
  if remain in wordDict: return myReturn(remain)
  for i in range(1,sz+1):
    pw = remain[0:i] # possible word. remain[0:n] would return the first n characters from "remain".
    print i, '= i, trying possible word', pw
    if pw in wordDict:    
      childResult = parse(remain[i:])
      if childResult == Hopeless: return Hopeless
      if childResult: 
        return myReturn(pw)    
    # The else block below is not needed to solve the problem. It's added purely for efficiency but I don't know any effective way to detct all Hopeless cases. 
    else: 
      if not check1char(remain[0]): return Hopeless # optimization for a common edge case
      
      # is pw a possible prefix? Locate the nearest 2 neighbours
      tmp = bisect.bisect_left(hay, pw)
      le = hay[tmp-1] if tmp>=1 else '<empty_str>'
      tmp = bisect.bisect_right(hay, pw)
      ri = hay[tmp]   if tmp<len(wordDict) else '<empty_str>'
      #print pw, 'not in wordDict. left/right are: ', le, '/', ri 
      if not   (le.startswith(pw) or ri.startswith(pw)):
        #print pw, 'is not a prefix of any word.. giving up on', remain
        return False;
  # end of for loop    
  return False       

def sol1(sentence): # one-pass
  sz = len(sentence)
  aboveWater = [False] * sz
  # Within the sentence, a position is "above water" if the char thereat is the last char of a known word, and we can hop off it.
  for idx in xrange(sz): 
    # print 'setting', idx
    for word in wordDict:
      hopBack = idx - len(word)
      if hopBack < -1: continue # to next word in wordDict, since current word is too long and we are near beginning of sentence
      
      if word == sentence [hopBack+1 : hopBack+1+len(word)]:
      # (assuming the word's size is 4) counting back from idx, the last 4 chars  matches the word:)
      
         # -1 means this word is at the start of sentence
        if hopBack == -1 or aboveWater[hopBack]:
           # print word, 'provides a hop from ', hopBack
           aboveWater[idx] = True #This position is reachable via some "dry ground", if we start from left end.
           break
  return aboveWater[-1] # a boolean to indicate punctuating completed or failed
  
def main():
  print wordDict
  print sol1("catsandog")
main()
'''Req: https://bintanvictor.wordpress.com/2018/02/24/splitcontinuoussentenceusingdictionary/
'''
