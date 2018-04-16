def solution(digit, start, end):
  assert (0 <= digit and digit <=9)
  ret =''
  for i in xrange(start, end+1):
    if digit > 0 and (i/100 == digit or i/10 == digit or i%10 == digit):    
      ret += str(i) + ' '
    elif digit == 0 and i%10 == 0:    
      ret += str(i) + ' '
  print ret
  return ret.strip()
def main():
  assert( solution(4,5,13) == '')
  assert( solution(3,1,13) == '3 13')
  assert( solution(3,5,23) == '13 23')
  assert( solution(1,0,12) == '1 10 11 12') # digit=1 is more tricky
  assert( solution(1,90,111) == '91 100 101 102 103 104 105 106 107 108 109 110 111') #
  assert( solution(0,5,23) == '10 20')
main()
''' Requirement: show all integers between start and end (inclusive) that shows the target digit
if none, the return empty string
'''