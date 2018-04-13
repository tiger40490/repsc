''' todo: more tests needed
showcase sorting a value in a dict
showcase __repr__ to support pprint
showcase split a string into an array
'''
import sys,bisect
from pprint import pprint

allrec = dict()

class Fill:
  def __init__(self, car, date, miles, fuel):
    self.car = car
    self.date = int(date)
    self.miles = float(miles)
    self.fuel = float(fuel)
  def __repr__(self):
    return self.__str__() # supports pprint
  def __str__(self):
    return self.car + ' ' + str(self.date) + ': miles=' + str(self.miles) + ' fuel=' + str(self.fuel);

def load():
  with open('data.txt') as f:
    lines = f.readlines()
  for line in lines:
    if  not line.strip(): continue
    tok = [x.strip() for x in line.split(',')]
    r = Fill(tok[1], tok[4], tok[2], tok[3])
    name = tok[0]
    if allrec.has_key(name):
      allrec[name].append(r)
    else:
      allrec[name] = [r] # new list added to dict

  for name in allrec:
    allrec[name].sort(key=lambda x: x.date)
  pprint (allrec)

def getMPG(name, d1, d2):
  if not allrec.has_key(name): return 'name not found'
  li = allrec[name]
  dates = [rec.date for rec in li]
  idx1 = bisect.bisect_left(dates, d1)
  idx2 = bisect.bisect_left(dates, d2)
  if idx2 == len(dates): 
    idx2 -= 1
    
  print li[idx1].date, li[idx2].date, " ... marks the 1st/last records to use"

  perCar = dict()
  for idx in range(idx1, idx2+1):#visit idx1~idx2 inclusive
    rec = li[idx]
    # put each Fill under the given car
    if perCar.has_key(rec.car):
      perCar[rec.car][0]+=rec.miles
      perCar[rec.car][1]+=rec.fuel
    else:
      perCar[rec.car]=[rec.miles, rec.fuel]

  for car in perCar:
    tmp = perCar[car]
    print car, tmp[0], tmp[1], tmp[0]/tmp[1]

def main():
  load()
  getMPG('John', 20160918, 20170922)

if __name__== "__main__": # best practice.. make this script usable as a module
    sys.exit(main())

# Requirement: https://wp.me/p74oew-3zx 
