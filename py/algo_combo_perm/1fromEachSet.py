'''
showcase passing generator output into another generator function. 
If you try to print list(theGenerator) for debugging, you would inadvertently exhaust all items. 
So It's better to construct a list from the generator output and pass in the list. 

showcase *args: passing, iterating, printing
'''
def gen(lists, nextset):
  #print 'in gen()', lists, nextset
  for b in nextset:
    for accu in lists:
      yield accu + str(b)	
def solve(*pool): #N set of strings, all unique
  print 'entering solve() with', pool
  output=list([''])
  for se in pool: # for each set in pool
    output = list(gen(output, set(se)))
  print 'returning', output
  return output #collection of concatenated strings

def test(exp, *args):
  output = solve(*args)
  assert len(output) == exp
test(18,  ['aa','ab', 'bb'], [11,12,22], ['x','xx'] )

'''Req: given N Sets of strings, all unique, pick one from each Set and concat the N strings as one output string. 
Generate all output strings.
'''
