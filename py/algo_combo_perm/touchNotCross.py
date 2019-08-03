def gen(func, pool, n):
  if n==0: yield []; return
  for pos, ch in enumerate(pool):
    for newlist in gen(func, func(pool, pos), n-1):
      yield [ch] + newlist
def abbr(word, n):
  def after_i_th(word, i):
    return word[i+1:]
  return gen(after_i_th, word, n)
# Once I had the above utilities written, the rest was just implementation challenge -- how fast you can get it working

def test(n):
  valid=[]
  for left in abbr(range(n*2), n): # leftBracketPositions
    #print left    
    if left[0] > 0: break #first left bracket must be at position 0
    cntRi = cntLe = 0
    validSequence=''
    for i,pos in enumerate(left):      
      if (i > 0): 
        rightInBetween = pos - left[i-1]-1
        cntRi += rightInBetween  
        validSequence += ')'*rightInBetween
      if cntLe < cntRi: break
      cntLe+=1
      validSequence += '('
    else:
      validSequence += ')' * (2*n - len(validSequence))
      valid.append(validSequence)
  print valid
  return len(valid)
      
assert test(3)==5
assert test(4)==14
assert test(5)==42

'''Req: https://wp.me/p74oew-8oE
'''