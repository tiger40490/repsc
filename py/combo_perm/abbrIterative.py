'''I wrote a recursive c++ solution to output in ascending order. 
Today I will forgo ascending order and try an iterative soution
Supose we have canned 3 chars in the word, and we have a collection of N abbreviations. 
For the next char 'j', we append 'j' to each existing abbr to generate N new abbreviations. 
Join the lists into a list of 2N.
'''
word="abbcd"
growing=set(['']) # start with a single empty string

def dump():
  print len(growing), growing
def add1char(ch):
  tmp = []
  for abbr in growing:
    tmp.append(abbr+ch)
  growing.update(tmp)
  dump()
  
def main():
  for ch in word:
    add1char(ch)
  
main()
