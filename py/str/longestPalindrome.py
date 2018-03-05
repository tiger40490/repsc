s="";
fulSz=1
maxSz=1

def countRep(pos): # counts how many of the given char repeats
  pass

def startfrom(l,r):#,isOdd):
  global maxSz
  assert l+1==r or l==r
  if l+1==r and s[l]!=s[r]: return 0
  
  cnt=min(l, fullSz-1-r) #how many chars to check on both sides
  #print 'cnt =',cnt
  #todo: check if the runway on both sides are long enough
  i=1
  for i in range(1,cnt+1):
    if s[l-i]!= s[r+i]: 
      i-=1
      break

  newLen=2*i+r-l+1
  if (newLen > maxSz):
        maxSz = newLen
        print newLen, ': found a longer palindrome :', s[l-i:r+i+1]

def run(orig): #print longest palindrome and its position
  global s, fullSz
  s=orig
  fullSz=len(orig)
  for i in range(1,fullSz-1):
    startfrom(i,i)
    startfrom(i,i+1)
    
def main():
  run('21211221121212')

main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has the my analysis

12:18 start
'''