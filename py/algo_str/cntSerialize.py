def compact(raw): #returns a compact form
  raw = raw.replace(' ','')+' ' #space as terminator
  if raw == '': return raw
  vec=[]
  repeat=1
  for i,ch in enumerate(raw):
    if i==0: continue #tolerable code smell
    if     raw[i-1] == ch: repeat += 1; continue
    assert raw[i-1] != ch
    vec.extend( [raw[i-1], repeat] )
    repeat = 1
  return ''.join(str(it) for it in vec)

assert compact('ab')  == 'a1b1'
assert compact('abbc')== 'a1b2c1'
assert compact('abb') == 'a1b2'
assert compact('aab') == 'a2b1'
assert compact('a') == 'a1'

'''Req: serialize a string by saving repetition count
clean, readable code
'''