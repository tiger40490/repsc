from collections import namedtuple

# the typename23 is not used anywhere. The base class is effectively anonymous
class SpecializiedFileReviewResult(namedtuple('typename23', 'path bytes')):
  ''' This class shows how to customize the __str__ of a namedtuple
  '''
  def __str__(self):
    basename=self.path.split('/')[-1]
    return basename+' bytes='+str(self.bytes)

def main():
  inst = SpecializiedFileReviewResult(path='/c/tmp/file1.txt', bytes=2313)
  print inst
  
main()