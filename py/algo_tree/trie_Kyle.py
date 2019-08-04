'''
todo: add tests

'''
class Trie:
  def __init__(self):
    # up to 26 sub-tries
    self.letters = dict()
  def hasThisLetter(self, letter):
    return letter in self.letters
  def addLetter(self, letter):
    if not self.hasThisLetter(letter):
      # hang a new empty trie off host node
      self.letters[letter] = Trie()
  def addWord(self, word):
      if len(word)==0: return
      ch = word[0]
      self.addLetter(ch)
      self.letters[ch].addWord(word[1:])
  def search(self, wordd):
    if len(word)==0: return True #????
    if hasThisLetter(word[0]): 
      return self.letters(word[0]).search(word[1:])
  def __repr__(self):
    return str(self.letters)

inst = Trie()
inst.addWord("dogs")
inst.addWord("doc")
print(inst.letters["d"].letters["o"])
print(inst.letters["d"])
print(inst)
#assert inst.search("doc")
#assert not inst.search("do")
'''
simple trie to represent a collection of words
'''