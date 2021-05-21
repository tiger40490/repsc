
class homeless(object):
  def __init__(self, id, payload):
    self.id = id # original pos
    self.val= payload
  def __str__(self):
    return str(self.id) + ' = original pos; payload = '+ str(self.val)
  

'''Req: you are given an array of positions, each a subscript into an original array.
Eg: [3,2,1,0] means after the reshuffle, it looks like [ a[3], a[2], a[1], a[0] ]. However, you need to do this in-situ, in O(1) space complexity, but you can modify the input array.
'''