'''
showcase simple VO class to simplify design and encapsulate.
showcase list clearing without rebinding the variable

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
  line[:]=[] # no "global" needed
  sz = len(origLine)
  vo = Vo(origLine[0])
  for i in range(1,sz):
    if vo.v==origLine[i]:
      vo.c+=1
      continue
    vo.save()
    vo=Vo(origLine[i])
  vo.save() 
  print line
  
def main():
  for _ in range(9):
    next()
main()

'''https://bintanvictor.wordpress.com/2018/02/07/look-n-say-sequence-fb/
I took 6 min to write the basic function on window and another 5 min to test it with one input
'''