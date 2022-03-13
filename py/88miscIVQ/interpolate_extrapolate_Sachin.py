'''
'''
from bisect import *
def slope(ins, price, le, ri):
  assert le < ri
  ret = float(price[ri] - price[le]) / float(ins[ri] - ins[le])
  print le, ri, 'slope=', ret
  return ret

def format2(flt):
  ret = "%.2f" %round(flt, 2)
  return ret
  
def interpolate(n, origI, origP):
  # first filter out bad prices
  instances=[]; price=[]
  for i in xrange(len(origP)):
    if origP[i] <= 0: continue
    price.    append(origP[i]);
    instances.append(origI[i])

  sz = len(price)
  lastid = sz-1 #lastIndex

  if sz == 1: return format2(price[0])
  assert sz >= 2
  
  if n < instances[0]:
    print n, 'is too low'
    slp = slope(instances, price, 0, 1)
    ret = -slp*(instances[0]-n) + price[0]
    return format2(ret)
  if instances[lastid] < n:
    print n, 'is too high'
    slp = slope(instances, price, lastid-1, lastid)
    ret = slp*(n-instances[lastid]) + price[lastid]
    return format2(ret)
    
  left = bisect_left(instances, n)
  print 'bisect returned', left
  if n == instances[left]: #exact match
    return format2(price[left])
    
  print n, 'is between', instances[left-1], instances[left]
  slp =  slope(instances, price, left-1, left)
  ret = slp*(n-instances[left]) + price[left]
  return format2(ret)
  
def test1(expected, n, ins, price):
  ret = interpolate(n, ins, price)
  print "returning", ret
  assert expected == ret

test1("54.25", 2, [10,25,50,100,500], [0, 0, 0, 0, 54.25])

# singular DB, with bad data
test1("5.00", 20, [50,5555], [5, 0])

# too high
test1("6.13", 1999, [10,25,50,100,500], [27.32, 23.13, 21.25, 18, 15.5])

# too low
test1("5.20", 20, [25,50,100], [5,4,3])

# in-between
test1("3.50", 75, [25,50,100], [5,4,3])

# exact match:
test1("2.46", 10, [10,25,50,100,500], [2.46, 2.58,2.0, 2.25, 3.0])
'''Req not easy to describe because this is not a typical algo question. As such, it doesn't deserve so much review.
'''
