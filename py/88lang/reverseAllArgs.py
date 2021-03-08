def reverse_args(f):
  return lambda *args : f(*args[::-1])

g = reverse_args(pow)
print g(2,3)

g = reverse_args(cmp)
print g(1,2)