class Trie:
  def __init__(self):
    # up to 26 sub-tries
    self.letters = dict()
  def isLetterIn(self, letter):
    return letter in self.letters
  def addLetter(self, letter):
    if not self.isLetterIn(letter):
      # hang a new empty trie off host node
      self.letters[letter] = Trie()
  def addWord(self, word):
    if word:
      ch = word[0]
      self.addLetter(ch)
      self.letters[ch].addWord(word[1:])
  def __repr__(self):
    return str(self.letters)

baseTrie = Trie()
baseTrie.addWord("dogs")
baseTrie.addWord("doc")
print(baseTrie.letters["d"].letters["o"])
print(baseTrie.letters["d"])
print(baseTrie)
'''
simple trie to represent a collection of words
'''