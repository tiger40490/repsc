def Tn(n):
  return 67-n*4 
def arithSeq():
  print "Enter a number for n: ",
  n = raw_input()
  print 'You entered n =', n
  actual = Tn(int(n))
  print 'The software has an output: ', actual

def any2digitNumber(xy):
  x = y = xx = yy = magic = 0
  # validate input
  # split into 2 digits x and y
  print [x,y], 'are the two digits of your input'
  # now subtract the sum from the original number
  print magic, 'is the (magic) number after subtracting from your input'
  # split magic into 2 digits xx and yy
  print xx+yy, 'is the sum of the magic two digits'
  assert xx+yy == 9
  
def getUserInput():
  print "Enter a two-digit number greater than 20 : ",
  n = raw_input()
  print 'You entered n =', n
  try:  
    any2digitNumber(int(n))
  except ValueError as e:
    print '\n\n    ',e
getUserInput()