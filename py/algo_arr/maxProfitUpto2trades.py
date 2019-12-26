# incomplete

def trade1day(li, verbose=1):
  s2=s1=0; b2=b1=-999999
  for unusedIndex,v in enumerate(li):
    s2=max(s2, b2+v)
    b2=max(b2, s1-v) 
    s1=max(s1, b1+v) # highest profit level
    b1=max(b1, -v) # smallest debt level
  print "\t\t ^ ^ returning max profit with 0,1 or 2 trades: $", s2
  return s2
    
def main():
  assert 0 ==trade1day([120,100,2,1])
  assert 100-1+119-2 ==trade1day([120,1,2,100,2,119])
main()
''' Req: blog
'''
