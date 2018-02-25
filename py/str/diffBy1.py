
def f1(a,b):
  if len(a) > len(b):
    l = list(a)
    s = list(b)
  else:
    l = list(b)
    s = list(a)
  for i in range(len(s)):
    if l[i] != s[i]:
      s.insert(0, l[i])
      return s == l
  return True

def f0(a,b):
  cnt=0
  for i in range(len(a)):
    if a[i] == b[i]: continue
    cnt += 1
   return cnt == 1
def oneEditApart(a,b):
  diff = abs(len(a) - len(b))
  if diff > 1 : return False
  if diff == 1: return f1(a,b)
  return f0(a,b)
def main():
  a='abc'
  b='abd'
  print oneEditApart(a,b)  
main()
'''see blog...
'''