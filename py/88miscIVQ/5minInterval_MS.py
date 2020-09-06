'''
showcase assertions on goodLineCnt == cumSize and size <= 5 to give much-needed quality assurance
showcase calling superclass ctor
'''
INVALID_FLOAT = -1
interval_length=10
isMktHourOnly =  True
isVerbose = True

class Interval:
  def __init__(self, windowStart=''):
    self.windowStart=windowStart # earliest minute permitted in this interval
    self.li=list()
    self.open=self.close=self.high=self.low=self.vol=INVALID_FLOAT
  def __repr__(self): # supports pprint
    return self.__str__()
  def __str__(self):
    return date + ',' + self.windowStart + ',' + self.open + ',' + str(self.high) + ',' + str(self.low) + ',' + self.close + ',' + str(self.vol)
    
class MiniInterval(Interval):
  def __init__(self, fields):
    Interval.__init__(self)
    #self.tstamp=fields[0]
    self.open =fields[1]
    self.close=fields[4]
    self.high =float(fields[2])
    self.low  =float(fields[3])
    self.vol  =float(fields[5])
    
class AggInterval(Interval):
  def __init__(self, window_Start=''):
    Interval.__init__(self, window_Start)
  def add(self, inInt):
    assert len(self.li) < interval_length 
    self.li.append(inInt)
  def wrapUp(self, adj=1):
    global cumSize
    if len(self.li)==0: return
    self.open = self.li[0].open
    self.close = self.li[-1].close
    self.high = max(mini.high for mini in self.li)
    self.low = min(mini.low for mini in self.li)
    self.vol = sum(mini.vol for mini in self.li)
    
    if isVerbose: print "wrap----up: size=", len(self.li), '[', self,']\n'
    assert len(self.li) <= interval_length
    cumSize += len(self.li)
    assert lineCnt-adj-skipCntA-skipCntB == goodLineCnt == cumSize , 'lineCnt = %d, skipCntA = %d, skipCntB = %d, goodLineCnt = %d, cumSize = %d' % (lineCnt, skipCntA, skipCntB, goodLineCnt, cumSize)
    if isVerbose: print >>outfile, self
    
# global variables:
windowStart=""
windowEnd=""
outInt=None
lineCnt = goodLineCnt = skipCntA=skipCntB = cumSize=0
date=''
outfile = None

def updateWindow(isIncremented=False):
  global outInt, windowStart, windowEnd
  HH,mm = windowStart.split(":")
  hour   = int(HH)
  minute = int(mm)
  if not isIncremented: minute += interval_length
  if minute == 60:
    minute = 0
    hour += 1
  windowStart = "%02d:%02d" % (hour, minute)
  windowEnd  = "%02d:%02d" % (hour, minute + interval_length - 1)
  outInt=AggInterval( window_Start = windowStart )
  if isVerbose: print '    windowStart updated to  ----> ' + windowStart, 'outInt size =', len(outInt.li)

def resetDate(newDate):
  global date, outInt, windowStart
  if outInt is not None:
    outInt.wrapUp() # must wrap up current object before updateWindow() wipes it out
  date = newDate
  windowStart="00:00"
  if isMktHourOnly: windowStart="09:30"
  updateWindow(True)

def load1file(filename="AM2"):
  global date, goodLineCnt, isVerbose, windowStart, outInt, lineCnt, goodLineCnt, skipCntA, skipCntB, cumSize, outfile
  windowStart=""
  outInt=None
  lineCnt = goodLineCnt = skipCntA=skipCntB = cumSize=0
  date=''
  outfile = open('5min_%s.txt' % filename, 'w');

  print '========================== vvvvvvvv  %s  vvvvvvvv ========' % filename
  f = open('c:/tmp/input1min/' + filename + '.txt', "r"); lines = f.readlines(); f.close()
  if len(lines) > 9999: isVerbose = False
  for line in lines:
    lineCnt += 1
    fields = line.strip().split(",")
    if isVerbose: print fields[:2]

    if fields[0] != date:
      resetDate(fields[0])
    
    fields=fields[1:]
    time = fields[0]
    if isMktHourOnly and 16 <= int(time.split(":")[0] ):
      if isVerbose: print time, ': input is after market close.... ignored';
      skipCntA += 1
      continue
    while windowEnd < time:
      outInt.wrapUp() # must wrap up current object before updateWindow() wipes it out
      updateWindow()

    if time < windowStart :
      if isVerbose: print time, ': input is Before market close.... ignored';
      skipCntB += 1
      continue    
    assert windowStart <= time <= windowEnd
    if True:
      mini = MiniInterval(fields)
      outInt.add(mini)
      if isVerbose: print windowStart + ' : adding to window: ', time, mini
      goodLineCnt += 1
    
  print 'final wrapUp() ... ZERO lineCnt adjustment needed'
  outInt.wrapUp(0)
  print 'lineCnt = %d, skipCntA = %d, skipCntB = %d, goodLineCnt = %d, cumSize = %d' % (lineCnt, skipCntA, skipCntB, goodLineCnt, cumSize)
  
def main():
  load1file('AA')
  load1file('AM2')
  load1file('AM')
main()
''' Req: https://wp.me/p74oew-9Sz 
'''