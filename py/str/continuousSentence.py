d = set(['al', 'ali', 'alice', 'bob', 'cody', 'dan'])
matched=list()

def myReturn(pw): # to reduce indentation levels
  global matched
  matched.insert(0, pw)  
  return True
def parse(s):
  sz = len(s)
  if sz == 0: return True
  for i in range(1,sz+1):
    pw = s[0:i] # possible word
    print 'trying', pw
    if pw in d:
      if parse(s[i:]): return myReturn(pw)
    else: # optimize as per Elvis
      print pw, 'not in dic'
  return False      
def main():
  result = parse('alialaliceal')
  print result, matched
main()
'''I think this is a classic algo question
Given a English dictionary of words (no numbers no underscores) and a long sentence. Someone has removed all the spaces. Now restore it by adding the spaces. If there's no way to parse the sentence just return False, otherwise return True. 

For this problem you don't need to output the words found but it should be easy.
'''