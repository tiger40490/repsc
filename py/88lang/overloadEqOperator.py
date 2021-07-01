''' showcase operator overloading
'''
class GlobalVO:
    def __init__(self, payload=None):
        self.payload = payload
    def __eq__(self, tgt):
        ret = (self.payload == tgt)
        print 'EQUAL' if ret else 'Not EQUAL'
        return ret
    def __ne__(self, tgt):
        return not self==tgt

instance = GlobalVO(5)
def test():
  assert instance != 44
  instance.payload=44
  assert instance == 44
test()
''' GlobalVO is useful when we have a global variable that need to be modified in a function but we don't want to use 'global' keyword
'''