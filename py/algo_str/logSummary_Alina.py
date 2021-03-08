'''
showcase re.sub() to remove quoted substring (containing spaces)

showcase file read/write using context manager. No file close needed.
'''
import re
from collections import defaultdict
def do1file(filename):
  hm = defaultdict(int)

  with open(filename) as infile:
    for line in infile:
      #print line
      line = re.sub(r'\[.*\]', '', line)
      line = re.sub(r'".*"', '', line)
      li=line.split()
      #print li
      host = li[0]
      bytes = li[-1] # last array-element
      hm[host] += int(bytes)

  with open('records_' + filename, 'w') as outfile :
    for k,v in hm.items():
      print k,v
      outfile.write(k+' '+str(v)+'\n')
  
# testing:
do1file("input.txt")