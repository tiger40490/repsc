'''showcase *args
'''
from fractions import gcd

def lcm2(a, b):
  return a*b // gcd(a,b)
  
def LCM(*args):
  # somehow, q[args] feels like a list
  
  if len(args) == 1: return
  # better put recursion exit condition here rather then "rightB4callingMyself". It serves as an assert len(args) > 1
  
  print args, '<-- are the remaining inputs. Tony will pick first two inputs\n ', args[0],args[1],' and compute their LCM: ',
  tmp = lcm2(args[0], args[1])
  print tmp
  return LCM(tmp, *args[2:])  # asterisk turns li into scalars 
  
LCM(10,20,30,40,50)