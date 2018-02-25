'''showcase: how to copy-truncate a list
'''
def f1(a,b):
  if len(a) > len(b):
    l = list(a)
    s = list(b)
  else:
    l = list(b)
    s = list(a)
    
  for i in range(len(s)):
    if l[i] != s[i]:
      s.insert(i, l[i])
      return s == l
  assert s == l[:-1] # modified copy with last 1 char chopped
  return True

def f0(a,b):
  cnt=0
  for i in range(len(a)):
    if a[i] == b[i]: continue
    cnt += 1
    #if cnt > 1: return False # I didn't add this because it's a low-value optimization but takes time and can create bug if not careful
  return cnt == 1

def OneEditApart(a,b):
  diff = abs(len(a) - len(b))
  if diff > 1 : return False
  if diff == 1: return f1(a,b)
  return f0(a,b)
  
def main():
  assert OneEditApart('a','b')  
  assert not OneEditApart("cat", "dog") 
  assert OneEditApart("cat", "cats") 
  assert OneEditApart("cat", "cut") 
  assert OneEditApart("cat", "cast") 
  assert OneEditApart("cat", "at")
  assert not OneEditApart("cat", "act") 
main()
'''see https://bintanvictor.wordpress.com/2018/02/07/edit-distance-fb80/ is the requirement

Took 40 minutes.
'''