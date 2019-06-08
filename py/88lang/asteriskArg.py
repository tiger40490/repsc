def simpleFunc(age, ssn, grade, status=''):
  print age, ssn, grade
def kwFunc(**kwa):
  print kwa
  
  
di={'age': 44, 'ssn': '123-45-6789', 'grade': 'A+'} 
status='GC'
rank='ED' 
simpleFunc(**di) # we CAN pass kwargs to a simple function
#simpleFunc(**locals()) #all locals must be declared as named parameters in simpleFunc() .. impractical
kwFunc(**di)
kwFunc(**locals())
'''Testing asterisk args
'''