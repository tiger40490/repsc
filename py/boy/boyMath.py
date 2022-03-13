def Tn(n):
  return 67-n*4 
def arithSeq():
  print "Enter a number for n: ",
  n = raw_input()
  print 'You entered n =', n
  actual = Tn(int(n))
  print 'The software has an output: ', actual

def any2digitNumber(xy):
  # validate input
  if xy > 99 or xy <= 20 :
    print xy, 'is out of range'
    return
  # split into 2 digits x and y
  x = xy/10
  y = xy - x*10
  print [x,y], 'are the two digits of your input'
  # now subtract the sum from the original number
  magic = xy - (x + y)
  print magic, 'is the (magic) number after subtracting from your input'
  # split magic into 2 digits xx and yy
  xx = magic/10 # follow line 14
  yy = magic - xx*10
  print [xx,yy], 'are the two digits of magic'
  print xx+yy, 'is the sum of the magic two digitss'
  assert xx+yy == 9
  
def getUserInput():
  print "Enter a two-digit number greater than 20 : ",
  n = raw_input()
  #n=20
  print 'You entered n =', n
  try:  
    any2digitNumber(int(n))
  except ValueError as e:
    print '\n\n    ',e
getUserInput()