from bisect import *

needle = 2
float_list = [0, 1.1, 2,2,2, 3.3, 4.4]

left = bisect_left(float_list, needle)
assert left == 2
print 'left (should be lower) =', left

right = bisect_right(float_list, needle)
assert right == 5
print 'right (should be higher) =', right
