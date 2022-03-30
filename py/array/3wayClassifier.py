'''showcase increments grouped together
'''
li = [12,312,4,81,6,89,8,708,183,4] # mutable
sz = len(li) # const
mm=0; hh=0

def classify(item):
  assert item > 0
  if item > 99: return 'H'
  if item > 9 : return 'M'
  return 'L'

def dump():
  print li
  print "mm is", li[mm], ", hh is", li[hh]
  
def printByCategory():
  global mm, hh
  for i in range(sz):
    cur=li[i]
    cat=classify(cur)
    if cat == 'L':
      del li[i]
      li.insert(mm,cur)
      mm += 1; hh +=1
      continue
    if cat == 'M':
      del li[i]
      li.insert(hh,cur)     
      hh +=1

def main():
  printByCategory()
  dump()
main()  
''' https://wp.me/p74oew-4Cj has the requirement in my blog
Warning -- python lists are vectors, so del keyword and insert() function are inefficient
'''
