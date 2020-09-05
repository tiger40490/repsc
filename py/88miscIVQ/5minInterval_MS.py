INVALID_FLOAT=-1
class Interval:
  def __init__(self, windowStart=''):
    self.windowStart=windowStart
    self.li=list() # should be fixed size 
    self.open=self.close=self.high=self.low=self.vol=INVALID_FLOAT
    pass
  def __repr__(self): # supports pprint
    return self.__str__()
  def __str__(self):
    return date + ',' + self.windowStart + ',' + str(self.open) + ',' + str(self.high) + ',' + str(self.low) + ',' + str(self.close) + ',' + str(self.vol)
    
class InInt(Interval):
  def __init__(self, fields):
    Interval.__init__(self)
    #print "input Interval size =", self.size
    self.open =float(fields[1])
    self.high =float(fields[2])
    self.low  =float(fields[3])
    self.close=float(fields[4])
    self.vol  =float(fields[5])
    print self
class AggInterval(Interval):
  def __init__(self, window_Start=''):
    Interval.__init__(self, window_Start)
    #print "output Interval size =", self.size
  def add(self, inInt):
    self.li.append(inInt)
  def wrapup(self):
    if len(self.li)==0: return
    self.open = self.li[0].open
    self.close = self.li[-1].close
    self.high = max(rec.high for rec in self.li)
    self.low = min(rec.low for rec in self.li)
    self.vol = sum(rec.vol for rec in self.li)
    print "wrap----up: size=", len(self.li), '[', self,']\n'
    print >>outfile, self
    
# global variables:
windowStart="00:00"
windowEnd=""
outInt=AggInterval() #window_Start=windowStart)
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
  outInt=AggInterval(window_Start=windowStart)
  #print '    windowStart updated to  ----> ' + windowStart, 'outInt size =', len(outInt.li)

def test(filename="AA"):
  global date, outInt, windowStart, windowEnd
  f = open('input1min/' + filename + '.txt', "r"); lines = f.readlines(); f.close()
  updateWindow()
  for line in lines:
    fields = line.strip().split(",")
    date = fields[0]
    
    fields=fields[1:] # drop first column
    #print fields
    time = fields[0]
    
    # every record must fall into a window!
    while windowEnd < time:
      outInt.wrapup()
      updateWindow()

    assert time <= windowEnd
    if windowStart <= time : # <= windowEnd: 
      rec = InInt(fields)
      outInt.add(rec)
      print windowStart + ' : adding to window: ', rec
  outInt.wrapup()
  
def main():
  test()
main()