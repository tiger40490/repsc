# if the 3 args are postive, then range() and slice are equivalent
start= 2
stop= 10
step= 7

li = range(0,stop)
print  'range is ',           range(start,stop,step)
print  li[start:stop:step]
assert li[start:stop:step] == range(start,stop,step)