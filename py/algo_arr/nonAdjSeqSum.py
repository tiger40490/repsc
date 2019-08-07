def solve(a):
  # initialize m_1 and m_2 for i=2
  m_2 = max(a[0], 0)
  m_1 = max(m_2, a[1])
  for i in xrange(2, len(a)):
    cur=a[i]
    print m_2, m_1, cur, '=cur, i=', i
    newSum = m_2 + a[i]
    m_0 = newSum if m_1 < newSum else m_1
    # before we increment i
    m_2, m_1 = m_1, m_0
  ret = max(m_2, m_1)
  print m_2, m_1, 'returning', ret
  return ret
assert 23 == solve([7, 2, -1, 8, 4,-3, 3,1,5])
assert 27 == solve([9,-6, 3, -9, 8, 7,-2,6,7])

'''Req: https://bintanvictor.wordpress.com/wp-admin/post.php?post=32575&action=edit

'''