'''
todo: clean up *args
showcase *args
'''
def gen(output, nextset):
  print 'in gen()', list(output), nextset
  for b in nextset:
    for a in output:
      yield a+b	
def dp(pool): #N set of strings, all unique
  print 'entering dp() with', pool
  output=list([''])
  for li in pool:
    output = list(gen(output, set(li)))
  return output #collection of concatenated strings
def test(exp, *args):
  output = dp( args[:] )
  assert len(output) == exp
test(9, ['aa','ab', 'bb'], ['11','12','22'] )
'''Req: given N Sets of strings, all unique, pick one from each Set and concate the N strings as one output. Generate all output.
'''