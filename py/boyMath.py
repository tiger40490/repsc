def Tn(n):
  return 67-n*4 

def arithSeq():
  print "Enter a number for n: ",
  n = raw_input()
  print 'You entered n =', n
  actual = Tn(int(n))
  print 'The software has an output: ', actual
arithSeq()
