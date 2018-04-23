'''
optimization todo: binary search
optimization todo: check for "(no genre" early or discard the movie if never needed
optimization todo

Q: would user pass in multiple genres?
Q: would user pass in wildcard genre?
'''
from pprint import pprint
from bisect import bisect_left #as bis

class Movie(object):
	def __init__(self, movie_id, title, genres, year):
		"""
		:param movie_id: id of movie. should be int, starting at 1
		:param title: movie title
		:param genres: list of genres movie is in
		:param year: year movie published.
		:return:
		"""
		self.id = movie_id
		self.title = title
		self.genres = genres
		self.year = year	
	def __repr__(self): # supports pprint
		return self.__str__()
	def __str__(self):
		#return str(self.id) + ' @' + str(self.year) + ':' + str(self.genres)+self.title
		return str(self.id) + ' ' + self.title # + str(self.year)


class Part1(object):
	def __init__(self, filename):
		self.li=[] 
		for line in open (filename): 
			if line.startswith('#'): continue
			li = line.upper().rstrip().split(',')
			assert len(li) == 4
			genlist=sorted(li[-1].split('|'))
			if genlist[0].startswith('(NO GENRE'):
				genlist=['NONE']
			#pprint(genlist)
			#pprint(li)
			self.li.append(Movie(li[0], li[1], genlist, int(li[2])))
			#print self.li[-1] 
		assert len(self.li) == 27278
		self.li.sort(key=lambda x: x.year)
		#pprint(self.li)

	def get_movies(self, genre, start_year, end_year):
		"""
		Returns list of Movie objects from the genre and between the year range
		:param genre: Genre to search for
		:param start_year: Inclusive start publication year
		:param end_year: Inclusive end publication year
		:return: list of Movie object defined in this document
		"""
		genre = genre.upper()
		assert start_year<=end_year
		#first = bisect_left(self.li, start_year) #doesn't work in python
		ret = []
		for mv in self.li:
		  if mv.year > end_year: break
		  if mv.year<start_year: continue
		  assert mv.year>=start_year and mv.year <= end_year
		  if genre in mv.genres:
			ret.append(mv)
		pprint(ret)
		return ret

inst = Part1("T:\\datafiles\\movies_formatted.csv")
def main():
  inst.get_movies('musical', 1891, 1894)
  #inst.get_movies('drama', 1992, 1992)
  #inst.get_movies('drama', 1992, 1993)
main()
