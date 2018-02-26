'''
showcase simple VO class to simplify design
'''
line=[1]
class Vo:
  def __init__(self, val):
    self.v=val
    self.c=1
  def pr(self):
    global line
    line.extend([self.c, self.v])
    #print self.c, self.v,

def next(s): # print next line
  global line
  line=list()
  sz = len(s)
  vo = Vo(s[0])
  for i in range(1,sz):
    if vo.v==s[i]:
      vo.c+=1
      continue
    vo.pr()
    vo=Vo(s[i])
  vo.pr() 
  return list(line)
  

def main():
  global line
  for _ in range(8):
    line = next(line)
    print line
  #next([1,1,1,2,2,1]);
main()

'''https://bintanvictor.wordpress.com/2018/02/07/look-n-say-sequence-fb/
I took 6 min to write the basic function on window and another 5 min to test it with one list
'''