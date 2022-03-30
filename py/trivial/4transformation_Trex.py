def div(num):
  while num%4 ==0:
    num = num/4;
    print num, 'after dividing by 4'
  if num%2 == 0:
    num = num/2;
    print num, 'after dividing by 2'
  return num
  
def do1(num):
  print 'v v v    original =', num
  while num != 0:
    num = div(num)
    if (num+1)%4 == 0:
      num +=1
      print num, 'after adding 1'
      continue
    num -= 1
    print num, 'after subtracting 1'
  #print '^^^ after while-loop, num =', num
  assert num == 0
  
def main():
  for i in range(5,9):
    do1(i)

main()  
'''https://bintanvictor.wordpress.com/2018/03/03/convert-to-0-using4transformations-trexquant/
'''
