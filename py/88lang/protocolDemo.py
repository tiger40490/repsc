'''
'''
class ProtocolBasedDict(object):
  ''' In this demo, by default 'a' maps to 1 and 'z' maps to 26
  any pair explicit set will override the default
  '''
  def __init__(self):
    self.override = dict()
  def __contains__(self, key): #part of an implicit protocol
    ret = key in self.override or len(key) == 1 and 'a' <= key <= 'z'
    print key, 'in ?', ret
    return ret
  def __setitem__(self, key, val): #part of an implicit protocol
    print len(self.override), 'len@internal_dict',
    self.override[key] = val
    print len(self.override)
  def __getitem__(self, key): #part of an implicit protocol
    print 'probing with', key
    if key in self.override: return self.override[key]
    assert len(key) == 1
    return ord(key) - ord('a') + 1
def test():
  map = ProtocolBasedDict()
  map['aa'] = 40490
  if 'aa' in map: print map['aa']
  if 'c'  in map: print map['c']
test()    
''' Based on [[python for the busy java developer]] P43-44
This technique is seldom needed in coding interviews, but illustrates the concept of protocol
'''