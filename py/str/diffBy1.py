def f1(a,b):
  if len(a) > len(b):
    l = list(a)
    s = list(b)
  else:
    l = list(b)
    s = list(a)
    
  for i in range(len(s)):
    if l[i] != s[i]:
      return s[i:] == l[i+1:]
  assert s == l[:-1] # modified copy with last 1 char chopped
  return True

def f0(a,b):
  for i in range(len(a)):
    if a[i] != b[i]: 
      return a[i+1:]==b[i+1:]    
  return False

def OneEditApart(a,b):
  diff = abs(len(a) - len(b))
  if diff > 1 : return False
  if diff == 1: return f1(a,b)
  return f0(a,b)
  
def main():
  assert OneEditApart('a','b')  
  assert OneEditApart('a','')  
  assert not OneEditApart('','')  
  assert not OneEditApart("cat", "cat") 
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