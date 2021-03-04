'''
re.sub() to replace every matched substr with a transformed version.
This technique uses capture group.

'''
import re
def betterCompression(s):
  table = [0] * 26
  readable = re.sub(r'([a-z])', r' \1 ', s)
  #print readable
  li = readable.split()
  sz = len(li); assert sz % 2 == 0
  for i in xrange(sz/2):
    ch  = li[2*i]
    frq = int(li[2*i + 1])
    table[ord(ch)-ord('a')] += frq
    #print ch, frq, table[ord(ch)-ord('a')]

  output=''
  for i in xrange(26):
    if table[i]:
      output += chr(i+97) + str(table[i])
  print output

betterCompression('a3c9b222c1')