'''
showcase reading first line, then read remaining lines into a list
'''
from pprint import pprint
import re,sys

isFirst=True
file1 = open('setDiff_input.txt', 'r')
tList=list(); eList=list();
szList1 = int(file1.readline().split()[0])

raw = file1.readlines()
for line in raw[:szList1]:
  tList.append(line.strip())

for line in raw[szList1:]:
  clean = re.sub(r"(\d\d\d\d\d\d\d\d)(\d\d)(\d\d)(\d\d)", r"\1-\2:\3:\4", line)
  eList.append(clean.strip())  

pprint (eList)
pprint (tList)
#sys.exit()
for aa in tList:
  if aa not in eList: print aa
for aa in eList:
  if aa not in tList: print aa  
'''
Req: first input lines specifies how many records in Tower format, and how many records in Exchange format. You need to check all Tower records and print any that's not matching any Exchange record. You need to check all Exch records and do the converse check.
'''