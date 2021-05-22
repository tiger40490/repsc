'''
todo: simplify

showcase: global variable list don't need 'global' keyword. Instead, you can reassign entire list with slice assignment

Variable naming reflects the metaphor, which is crucial to the comprehension of this algo.
'''
FILLED = -1 # indicates a target slot is not to be filled again
a=list()

class homeless(object):
  def __init__(self, id, payload):
    self.id = id # original pos
    self.val= payload
  def __str__(self):
    return str(self.id) + '=old_pos..payload='+ str(self.val)

def dump(d):
  print '  '.join(a), '<-- a[]'
  print '  '.join(str(i%10) for i in xrange(sz))
  print ' '.join( '%-2d' %p for key, p in sorted(d.iteritems())), '<---- newTenantIdAt'

def solve(input):
  a[:]=list('ABCD')
  global sz; sz=len(a)
  newTenantIdAt = {pos: newTenentId for pos, newTenentId in enumerate(input)}
  # dict is (slower but) slightly more intuitive than array
  assert len(newTenantIdAt) == sz
  assert range(sz) == sorted(newTenantIdAt.values())
  
  for k,v in newTenantIdAt.iteritems(): 
    if k==v: newTenantIdAt[k] = FILLED # minor optimization .. avoid unnecessary work
  ##### initialization done
  
  scanStart = 0
  while True:
    print 'sanning for first unfilled curTargetHome from ..', scanStart
    for i in xrange(scanStart, sz):
      if newTenantIdAt[i] == FILLED: continue
      curTargetHome = evictedId = scanStart = i # first unfilled curTargetHome
      theHomeless = homeless(evictedId, a[evictedId]) 
      print 'theHomeless is ', theHomeless #only 1 homeless
      break
    else:
      print ' '*30 + '^ ^ ^ ^   All positions filled   ^ ^ ^ ^'
      return ''.join(a)

    # Here's the main loop. Dense and hard to follow
    while True: #one round
      if newTenantIdAt[curTargetHome] == theHomeless.id: 
        a[curTargetHome] = theHomeless.val
        newTenantIdAt[curTargetHome] = FILLED
        dump(newTenantIdAt)
        break
      tenantOldHome = newTenantIdAt[curTargetHome]       
      a[curTargetHome] = a[tenantOldHome] #copy the payload from tenantOldHome to curTargetHome
      dump(newTenantIdAt)
      newTenantIdAt[curTargetHome] = FILLED # to indicate curTargetHome is filled
      # Now tenantOldHome is vacant, so tenantOldHome becomes the new curTargetHome
      curTargetHome = tenantOldHome 
      
def main():
  assert 'ACBD'==solve([0,2,1,3]) # one round enough
  #return
  assert 'DCBA'==solve([3,2,1,0]) # two rounds
  assert 'BADC'==solve([1,0,3,2]) # two rounds
  assert 'BCDA'==solve([1,2,3,0]) # one round enough
  assert 'BACD'==solve([1,0,2,3]) # one small round enough.
  assert 'ABCD'==solve([0,1,2,3]) # no change
  
main()
'''Req: you are given an array of positions, each a subscript into an original array.
Eg: [3,2,1,0] means after the reshuffle, the array should look like [ a[3], a[2], a[1], a[0] ]. However, you need to do this in-situ, in O(1) space complexity, but you can modify the input "instruction" array in adition to the original array.
Time complexity is less important.
'''