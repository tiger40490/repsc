s=''
fulSz=1
winnerSz=1
winner=''

def startfrom(l,r):
  global winnerSz,winner
  assert l+1==r or l==r
  if l+1==r and s[l]!=s[r]: return
  
  cnt=min(l, fullSz-1-r) #how many chars to check on both sides
  if cnt*2+r-l+1 <=winnerSz: return
  
  for i in range(1,cnt+1):
    if s[l-i]!= s[r+i]: 
      i-=1
      break
  newLen=2*i+r-l+1
  if (newLen > winnerSz):
        winnerSz = newLen
        winner = s[l-i:r+i+1]
        print 'found a longer palindrome :', winner

def run(haystack): 
  global s, fullSz
  s=haystack
  fullSz=len(s)
  for i in range(1,fullSz-1):
    startfrom(i,i)
    startfrom(i,i+1)
  return winner
    
def main():
  assert '212112211212' == run('21211221121212')

main()
'''https://bintanvictor.wordpress.com/2018/03/04/find-longest-palindrome-substring-unsolved/ has the my analysis
'''
