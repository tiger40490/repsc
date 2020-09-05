'''
todo: date may not be the same!
todo: updateWindow() to rename to ...
'''
INVALID_FLOAT = -1

class Interval:
  def __init__(self, windowStart=''):
    self.windowStart=windowStart
    self.li=list() # should be fixed size 
    self.open=self.close=self.high=self.low=self.vol=INVALID_FLOAT
  def __repr__(self): # supports pprint
    return self.__str__()
  def __str__(self): # format as required
    return date + ',' + self.windowStart + ',' + self.open + ',' + str(self.high) + ',' + str(self.low) + ',' + self.close + ',' + str(self.vol)
    
class MiniInterval(Interval):
  def __init__(self, fields):
    Interval.__init__(self)
    #print "input Interval size =", self.size
    #self.tstamp=fields[0]
    self.open =fields[1]
    self.close=fields[4]
    self.high =float(fields[2])
    self.low  =float(fields[3])
    self.vol  =float(fields[5])
    #print self
    
class AggInterval(Interval):
  def __init__(self, window_Start=''):
    Interval.__init__(self, window_Start)
  def add(self, inInt):
    assert len(self.li) <=4
    self.li.append(inInt)
  def wrapUp(self):
    global cumSize
    if len(self.li)==0: return
    self.open = self.li[0].open
    self.close = self.li[-1].close
    self.high = max(rec.high for rec in self.li)
    self.low = min(rec.low for rec in self.li)
    self.vol = sum(rec.vol for rec in self.li)
    #print "wrap----up: size=", len(self.li), '[', self,']\n'
    assert len(self.li) <= 5
    cumSize += len(self.li)
    assert lineCnt == cumSize, 'lineCnt = %d, cumSize = %d' % (lineCnt, cumSize)
    print >>outfile, self
    
# global variables:
windowStart="00:00"
windowEnd=""
outInt=None
lineCnt=cumSize=0
date=''
outfile = open('5min.out', 'w');

def updateWindow(): # to rename
  global outInt, windowStart, windowEnd
  HH,mm = windowStart.split(":")
  minute = int(mm) + 5
  hour   = int(HH)
  if minute == 60:
    minute = 0
    hour += 1
  windowStart = "%02d:%02d" % (hour, minute)
  windowEnd  = "%02d:%02d" % (hour, minute+4)
  outInt=AggInterval( window_Start = windowStart )
  #print '    windowStart updated to  ----> ' + windowStart, 'outInt size =', len(outInt.li)

def resetDate(dt):
  global date, outInt, windowStart
  if outInt is not None:
    outInt.wrapUp() # must wrap up current object before updateWindow() wipes it out
  date = dt
  windowStart="00:00"
  updateWindow()

def load1file(filename="AM"):
  global date, lineCnt
  f = open('input1min/' + filename + '.txt', "r"); lines = f.readlines(); f.close()
  for line in lines:
    fields = line.strip().split(",")
    #print fields[:2]

    if fields[0] != date:
      resetDate(fields[0])
    
    fields=fields[1:]
    time = fields[0]
    while windowEnd < time:
      outInt.wrapUp() # must wrap up current object before updateWindow() wipes it out
      updateWindow()

    assert windowStart <= time <= windowEnd
    rec = MiniInterval(fields)
    outInt.add(rec)
    #print windowStart + ' : adding to window: ', time, rec
    lineCnt += 1
  outInt.wrapUp()
  print 'lineCnt = %d, cmSize = %d' % (lineCnt, cumSize)
  
def main():
  load1file()
main()
''' Req: see email from Deepak'''