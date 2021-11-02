'''showcase *args
'''
from fractions import gcd

def lcm2(a, b):
  return a*b // gcd(a,b)
  
def LCM(*args):
  # somehow, args feels like a list
  if len(args) == 1: return
  # better put the recursion terminal condition here. It serves as an assert len(args) > 1
  
  print args, '<-- are the remaining inputs. Tony will pick first two inputs\n ', args[0],args[1],' and compute their LCM: ',
  tmp = lcm2(args[0], args[1])
  print tmp
  li = [tmp]; li.extend(args[2:])
  return LCM(*li)  
  
LCM(10,20,30,40,50)