from bisect import *

needle = 2
float_list = [0, 1.0, 2, 2, 2, 5.0]

left = bisect_left(float_list, needle)
assert left == 2
print 'bisect_le (should be lower) =', left

right = bisect_right(float_list, needle)
assert right == 5
print 'bisect_ri (should be higher) =', right

# if no hit, then both return the same
needle=2.99999
left = bisect_left(float_list, needle)
right = bisect_right(float_list, needle)
assert left == right == 5