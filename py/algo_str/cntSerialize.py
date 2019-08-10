def do(raw): #returns a compact form
  raw = raw.replace(' ','')
  if raw == '': return raw
  vec=[raw[0]]
  repeat=1
  for i,ch in enumerate(raw):
    if i==0: continue
    if raw[i-1] == ch: repeat += 1; continue
    assert raw[i-1] != ch
    vec.append(str(repeat))
    vec.append(ch)
    repeat = 1
  vec.append(str(repeat))
  ret = ''.join(vec)
  print ret
  return ret

assert do('ab')  == 'a1b1'
assert do('abbc')== 'a1b2c1'
assert do('abb') == 'a1b2'
assert do('aab') == 'a2b1'

'''Req: serialize a string by saving repetition count
clean, readable code
'''