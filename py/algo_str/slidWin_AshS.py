'''
todo: fix broken tests
'''

def solve2(ss, k, charValue): #by Ashish
    if (len(ss) == 1):
        print 'returning', 1
        return 1;
    badChars = set()
    assert len(charValue) == 26
    for i in xrange(26):
        if charValue[i] == '0':
            badChars.add(chr(ord('a') + i))

    left_index = 0
    right_index = 0
    count = 0
    window_size = 0;

    for current_index in xrange(0, len(ss)):
        if ss[current_index] in badChars:
            if count <= k:
                count = count + 1
            elif count > k:
                if ss[left_index] in badChars:
                    count = count - 1
                left_index = left_index + 1
                count = count + 1
        else:
            if count > k:
                if ss[left_index] in badChars:
                    count = count - 1
                left_index = left_index + 1

        right_index = current_index
        if count <= k and window_size < (right_index - left_index + 1):
            window_size = right_index - left_index + 1

    print 'returning', window_size
    return window_size
def solve1(ss, k, charValue): # one-pass sliding window
    badChars = set()
    assert len(charValue) == 26
    for i in xrange(26):
        if charValue[i] == '0':
            badChars.add(chr(ord('a') + i))
    print badChars

    le = 0; cnt = 0  # invariance: cnt <= k
    for char in ss[:k]:
        if char in badChars: cnt += 1
    if(len(ss) == 1): ret = 1
    else: ret = k # initialize to k
    print 'initial window of size k has', cnt, 'bad characters'
    # le and cnt all initialized. Now start sliding an expanding window
    
    for ri in xrange(k - 1, len(ss) - 1): # why len()-1? is ri in the window? yes
        print '\nafter validating, new le=', le, '; new ri=', ri, '; cnt=', cnt

        if cnt > k:  # slide the window
            if ss[le] in badChars: cnt -= 1
            le += 1
            print 'new le====', le
            if ss[ri + 1] in badChars: cnt += 1
            continue

        assert cnt <= k  # expand by moving ri
        if True:
            print 'fwd-checking', ss[ri + 1]
            if ss[ri + 1] in badChars:
                cnt += 1
                print 'new cnt===', cnt, 'may need to slide'
            if cnt <= k:
                winSz = ri + 2 - le
                print 'bigger window sz=', winSz
                if winSz > ret: ret = winSz

    print 'returning', ret
    return ret
def solve(ss, k, charValue):
  return solve1(ss, k, charValue)

assert solve('a', 2,'10101111111111111111111111') == 1
assert solve('ac', 2,'10101111111111111111111111') == 2
assert solve('ac', 2,'10101111111111111111111111') == 2
assert solve('abcdeddddddddaaaaaaaaaa', 2,'10101111111111111111111111')  == 12
assert solve('ddddaa', 3,'10101111111111111111111111')  == 5
print '--------------------------'
assert solve('abcdeaa', 2,'00101111111111111111111111') == 4
""" not so worthwhile, but I did put in a few hours, so let's review and keep this code

Problem statement: Intelligent Substring 
There are two types of characters in a particular language: special and normal.

Given string s, return the longest substring of s that contains at most k normal characters.
Whether a character is normal is determined by a 26-digit bit string named charValue.
Each digit in charValue corresponds to a lowercase letter in the English alphabet.

Example:
    s = 'abcde'
For clarity, the alphabet is aligned with char
    alphabet = abcdefghijklmnopqrstuvwxyz
    charValue= 10101111111111111111111111
The only normal characters in the language (according to charValue) are b and d.
The string s contains both of these characters.

For k = 2, the longest substring of s that contains at most k = 2 normal characters is 5 characters long, abcde, so the return value is 5.

If k = 1 instead, then the possible substrings are 'a', 'b', 'c', 'd', 'e', 'ab', 'bc', 'cd', 'de', 'abc', 'cde'. The longest substrings are 3 characters long, which would mean a return value of 3.
"""