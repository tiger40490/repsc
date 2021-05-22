'''
todo: improve var naming
todo: simplify

'''
a=['A','B','C', 'D']
newTenantIdAt=list()
sz=len(a)

class homeless(object):
  def __init__(self, id, payload):
    self.id = id # original pos
    self.val= payload
  def __str__(self):
    return str(self.id) + '=old_pos..payload='+ str(self.val)

def dump():
  print '  '.join(a), '<-- a[]'
  print '  '.join(str(i%10) for i in xrange(sz))
  print ' '.join( '%-2d' %p for p in newTenantIdAt), '<---- newTenantIdAt'

def solve(input):
  global newTenantIdAt; newTenantIdAt=input
  assert len(newTenantIdAt) == sz
  assert reduce((lambda x,y: x+y*y), newTenantIdAt)==reduce((lambda x,y: x+y*y), xrange(sz))
  
  while True:
    for i in xrange(sz):
      if newTenantIdAt[i] == -1: continue
      targetPos = i
      shelter = homeless(targetPos, a[targetPos]); print 'shelter has: ', shelter
      break
    else:
      print 'All positions filled'
      break
    while True: #one round
        sourcePos = newTenantIdAt[targetPos] # evictedId ??
        if sourcePos == shelter.id: 
          a[targetPos] = shelter.val
          newTenantIdAt[targetPos] = -1
          dump()
          break
        a[targetPos] = a[sourcePos] #copy the payload from sourcePos to targetPos
        dump()
        newTenantIdAt[targetPos] = -1 # to indicate targetPos filled
        targetPos = sourcePos
def main():
  #solve([1,2,3,0]) # one round enough
  solve([1,0,3,2]) # two rounds
  #solve([1,0,2,3]) # one small round enough.
main()
'''Req: you are given an array of positions, each a subscript into an original array.
Eg: [3,2,1,0] means after the reshuffle, it looks like [ a[3], a[2], a[1], a[0] ]. However, you need to do this in-situ, in O(1) space complexity, but you can modify the input array.
'''