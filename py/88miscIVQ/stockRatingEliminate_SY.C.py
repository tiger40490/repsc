def solution(m):
  n = int(m[0][0])
  p = int(m[1][0])
  finalRating=dict()
  names=list()
  
  for tmp in xrange(n):
    nid=tmp+2
    for pid in xrange(p):
      name,rating = m[nid][pid].split(':')
      #print nid, pid, '-->', m[nid][pid], name, rating
      if name not in finalRating: names.append(name)
        #print name , 'not in', names
      finalRating[name]=rating 
   
  for name in names: print finalRating[name]
#  print finalRating , names

input=[[2],
       [3],
       ['p1:a', 'p3:b', 'p5:x'],
       ['p1:b', 'p2:q', 'p5:x']
      ]
solution(input)
''' Req: see 21 May 2023 email

'''