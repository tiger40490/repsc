'''
i will keep two arrays at each matrix cell. Each an array of indices into x and into y
'''
#x=y=''

def bu(): #bottom-up.. returns a string??
  pass
def cleanup(dirtyX,dirtyY):
  global x,y,m
  x = dirtyX.replace(' ','')
  y = dirtyY.replace(' ','')
  m = [['_' for _ in range(len(x))] for _ in range(len(y))]
  for s in [x,y]:
    print ' '+('  '.join(list(s)))
    for i in range(len(s)): print '%2s' % i,  
    print '\n'
  return bu()
def main():
  cleanup('ababaababbab', 'aabbaabaabbbabbab')
main()
'''Req: longest common subsequence (not sub-string) between two strings X and Y
'''