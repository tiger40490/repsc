'''
showcase simple VO class to simplify design and encapsulate.
showcase list clearing without rebinding the variable

global vs arg -- In most cases global var is simpler for timed coding
tests, but in this case, passing (by value) input list and  output list 
every time is simpler. Here's the more efficient design --

Since Vo.save() needs to update "line", it should be a global var (i.e. module variable), so next() should not take in arg
'''
line=[1]
class Vo:
  def __init__(self, val):
    self.v=val
    self.c=1
  def save(self):
    line.extend([self.c, self.v])

def next(): 
  origLine=list(line)
  sz = len(origLine)
  vo = Vo(origLine[0])
  line[:]=[] # no "global" needed
  for i in range(1,sz):
    if vo.v==origLine[i]:
      vo.c+=1
      continue
    vo.save()
    vo=Vo(origLine[i])
  vo.save() 
  print line
  
def test():
  for _ in range(9):
    next()
  assert line == [1, 3, 2, 1, 1, 3, 1, 1, 1, 2, 3, 1, 1, 3, 1, 1, 2, 2, 1, 1]
test()

'''https://bintanvictor.wordpress.com/2018/02/07/look-n-say-sequence-fb/
I took 6 min to write the basic function on window and another 5 min to test it with one input
'''
