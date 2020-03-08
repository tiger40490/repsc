from pprint import pprint
def solve(inputs):
  pprint(inputs)
  assert len(inputs) > 0
  countOfOnes = len(inputs[0])
  assert countOfOnes > 0
  origIdx=dict()
  for i in xrange(len(inputs)):
    aDNA = inputs[i]
    assert countOfOnes == len(aDNA), 'each aDNA must have the same count of ones'
    inputs[i] = tuple(sorted(aDNA, reverse=True))
    origIdx[inputs[i]] = i

  #pprint(origIdx)
  #pprint(inputs)
  return [ origIdx[sortedDNA] for sortedDNA in sorted(inputs, reverse=True) ]
  #print ret
  #return ret
    
def main():
  assert [1,2,0] == solve([[0,2], [2,3], [2,1]]) # sample case 0
  assert [1,0] == solve([[0,1,2], [3,1,0]]) # sample case 1
  assert [1,0,2] == solve([[1], [2], [0]]) # sample case 2
main()
'''Req (see email 1Mar2020): given N (say 222) binary number, if we represent each as a bit-set of various lengths, we know each bit-set contains equal number of ones. We want to sort these 222 binary numbers, but each bit set is "jumbled up" -- If a bit-set has positions 0,5,29,76,104 turned on, then this binary number is given as [5,104,29,76,0] or some other shuffle of the indices.
'''