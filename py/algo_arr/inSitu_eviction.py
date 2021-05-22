'''
add asserts to tests
todo: improve var naming
todo: simplify

'''
FILLED = -1 # indicates a target slot is not to be filled again
newTenantIdAt=list()
a=['A','B','C', 'D']

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
  a[:]=['A','B','C', 'D']
  newTenantIdAt[:]=input # to help dump()
  global sz; sz=len(a)
  assert len(newTenantIdAt) == sz
  assert reduce((lambda x,y: x+y*y), newTenantIdAt)==reduce((lambda x,y: x+y*y), xrange(sz))
  
  while True:
    for i in xrange(sz):
      if newTenantIdAt[i] == FILLED: continue
      targetPos = i
      shelter = homeless(targetPos, a[targetPos]) #only 1 homeless guy in shelter
      print 'shelter has: ', shelter
      break
    else:
      print 'All positions filled'
      return ''.join(a)
    while True: #one round
        sourcePos = newTenantIdAt[targetPos] # evictedId ??
        if sourcePos == shelter.id: 
          a[targetPos] = shelter.val
          newTenantIdAt[targetPos] = FILLED
          dump()
          break
        a[targetPos] = a[sourcePos] #copy the payload from sourcePos to targetPos
        dump()
        newTenantIdAt[targetPos] = FILLED # to indicate targetPos filled
        targetPos = sourcePos
def main():
  assert 'BCDA'==solve([1,2,3,0]) # one round enough
  assert 'BADC'==solve([1,0,3,2]) # two rounds
  assert 'BACD'==solve([1,0,2,3]) # one small round enough.
main()
'''Req: you are given an array of positions, each a subscript into an original array.
Eg: [3,2,1,0] means after the reshuffle, it looks like [ a[3], a[2], a[1], a[0] ]. However, you need to do this in-situ, in O(1) space complexity, but you can modify the input array.
'''