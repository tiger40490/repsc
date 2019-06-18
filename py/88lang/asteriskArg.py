'''I think the ** operator unpacks a dictionary
'''
def simpleFunc(age, ssn, grade, status=''):
  print 'in simpleFunc()', age, ssn, grade, status
def kwFunc(**kwa):
  print kwa
  
  
di={'age': 44, 'ssn': '123-45-6789', 'grade': 'A+'} 
simpleFunc(**di) # we CAN pass kwargs to a simple function
d2={'age': 44, 'ssn': '123-45-6789', 'grade': 'A+', 'status': 'GC'} 
simpleFunc(**d2)

#simpleFunc(**locals()) #all locals must be declared as named parameters in simpleFunc() .. impractical

print '----'

kwFunc(**di)
kwFunc(**locals()) # fine
'''Testing a few usages of asterisk args
'''