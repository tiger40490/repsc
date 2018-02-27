li = [12,312,4,81,6,89,8,708,183,4]
sz = len(li)

def classify(item):
  assert item > 0
  if item > 99: return 'H'
  if item > 9 : return 'M'
  return 'L'

def dump():
  print li
  
def printCategories():
  mm=0; hh=0
  for i in range(sz):
    cur=li[i]
    cat=classify(cur)
    if cat == 'L':
      del li[i]
      li.insert(mm,cur)
      mm += 1; hh +=1
    elif cat == 'M':
      del li[i]
      li.insert(hh,cur)     
      hh +=1
def main():
  printCategories()
  dump()

main()  