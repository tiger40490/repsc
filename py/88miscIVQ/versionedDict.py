'''
showcase dict clone
showcase initialize a dict without quotes around string keys
'''
class solFastRead:
  ''' Something like Design 5 in my blogpost -- O(1) read; write takes linear time to clone entire vector of key/value pairs.
  
 Specificlaly, If after N writes there are K keys, then write is O(K).
  '''
  def __init__(self):
    self.li=list() #each element represents a version, is a dict of key/value pairs
    self.li.append(dict()) #empty dict is versiion 0
    self.lid = -1 + len(self.li)
  def read(self, vid):
    ret = self.li[vid]
    return ret
  def write(self, k, v):
    new = dict(self.li[self.lid])#clone
    new[k]=v
    self.li.append(new)
    self.lid += 1
    assert self.lid+1 == len(self.li)
def main():
  sol=solFastRead()
  assert len(sol.read(0)) == 0
  assert sol.lid == 0
  sol.write('k1', 101)
  sol.write('k2', 202)
  sol.write('k1', 103)
  sol.write('k1', 104)
  assert sol.read(4) == dict(k1=104, k2=202)
main()
'''Req: Suppose a resume consists of key/value pairs of strings. Within a resume, these keys are non-repeating. We need to optimize two operations
* Each update(key, value) operation creates or updates a key with a new value, and returns an incremented vid as an int
* Each getResume(vid) returns a key/value dictionary at the specified snapshot
* I think in a realistic syste, we also need a deleteVersion(vid)

By definition, the initial version is an empty version 0.
'''