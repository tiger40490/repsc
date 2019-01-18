def prec(anything):
  s=str(anything)
  if '.' not in s: return -1
  sz = len(s)
  assert s[-1] != '.', 'a number would never end in a dot' 
  idx = s.index('.')
  return len(s)-s.index('.')-1;
  
def match(A, B):
  pA = prec(A)
  pB = prec(B)
  # print pA, A, '\n', pB, B
  sB = str(B)
  if pA < pB:
    keep = len(sB)-pB+pA
    if pA == -1:
      ret = int(sB[:keep])
    else:
      ret = float(sB[:keep])
  else:
    ret =B
  print 'returning', B
  return ret

def main():
  assert match(A=8, B=4) == 4
  assert match(A=1, B=0.66789363) == 0
  assert match(A=0.01, B=0.66789363) == 0.66
  assert match(A=0.0067, B=0.06375813) == 0.0637
  assert match(A=0.001, B=0.67) == 0.67
  assert match(A=0.1, B=0.678) == 0.6
main()