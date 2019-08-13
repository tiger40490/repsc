'''
todo: add tests
feature: use explicit sentinel to enhance clarity and reduce ambiguity

https://leetcode.com/problems/implement-trie-prefix-tree/solution/ java solution is similar.
'''
class Trie:
  def __init__(self):
    # up to 26 sub-tries
    self.nextLetters = dict() #letter->sub-trie
  def hasThisLetter(self, letter):
    return letter in self.nextLetters
  def addLetter(self, letter):
    if not self.hasThisLetter(letter):
      # hang a new empty trie off host node
      self.nextLetters[letter] = Trie()
  def addWord(self, word):
      if len(word)==0: return
      ch = word[0]
      self.addLetter(ch)
      self.nextLetters[ch].addWord(word[1:])
  def isSentinel(self):
    return 0==len(self.nextLetters)
  def search(self, word):
    if len(word)==0: return self.isSentinel()
    print 'seeking', word, 'among', self.nextLetters.keys()
    if not self.hasThisLetter(word[0]): return False
    return self.nextLetters[word[0]].search(word[1:])
  def __repr__(self):
    return 'SEN ' if self.isSentinel() else str(self.nextLetters)

inst = Trie()
inst.addWord("dogs")
inst.addWord("doc")
print(inst.nextLetters["d"].nextLetters["o"])
print(inst.nextLetters["d"])
print(inst)
assert inst.search("doc")
assert not inst.search("dog")
assert not inst.search("do")
assert not inst.search("o")
'''
simple trie to represent a collection of words
'''