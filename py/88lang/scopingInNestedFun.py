'''
todo: nested function to reseat a ref using idic
'''
from copy import deepcopy
from pprint import pprint
import inspect, sys
def main():
  def broken1():
    # no permanent effect -- only reseats a local ptr variable, just like in java
    tupleInMain = ('tupleInMain', 11,13)    
  def usingGlobal(): # make globalvar a module-level ptr, so as to reseat it
    global globalvar; # needed!
    globalvar = ('globalvar', 11)
  def using_Local_Obj_Holder(): # lookup is effectively used as a namespace
    lookup['myVarOld'] = lookup['myVar'] #completely optional
    lookup['myVar'] = (0.003, -555)
  def using_idic():
    clone = inspect.currentframe().f_back.f_locals
    clone['tupleInMain']=('tupleInMain', 11,13)
    print clone['tupleInMain'], 'inside using_idic()'
    
  ############
  tupleInMain=alias231=('tupleInMain', 8,5,2)
  print tupleInMain, '= orginal'
  broken1()
  print tupleInMain, 'after broken1(), the local var is unaffected'
  assert id(alias231)==id(tupleInMain)
  using_idic()
  print tupleInMain, 'after using_idic(), the local var is unaffected'
  assert id(alias231)==id(tupleInMain)
    
  ############  
  global globalvar; # needed
  globalvar=alias97=('globalvar', 2,3,5,7)
  usingGlobal()
  print globalvar
  assert id(alias97) != id(globalvar)
  
  ############
  lookup={'myVar': (98,21)}
  clone=deepcopy(lookup)
  assert clone == lookup
  using_Local_Obj_Holder()
  assert clone != lookup
  print lookup , '<- shows both the new object and original object:)'
  
main()
'''nested function to reseat a ref, based on 
https://stackoverflow.com/questions/7935966/python-overwriting-variables-in-nested-functions
'''