'''
'''
def missingWords(strS, strT):
  # split into two arrays
  ss = strS.split(); szS=len(ss)
  tt = strT.split(); szT=len(tt)
  #print ss, tt
  iS = iT = 0
  ret = list()
  while iS < szS: 
    cdd = ss[iS]
    tgt = '' if iT == szT else tt[iT]
    print cdd, '^', tgt
    if cdd == tgt:
      iT +=1
    else:
      #print '   missing in subsequence', cdd
      ret.append(cdd)  
    iS +=1
  #print ret
  return ret

missingWords('i am using Hacker to improve programming', 'am Hacker to improve')
'''
req: strT (bad words) is guaranteed to be a subsequence of strS. Return the good words in strS.
'''