'''
todo: nested function to reseat a ref using 'global'
todo: nested function to reseat a ref using idic
'''
def main():
  def broken1():
    # no permanent effect -- only reseats a local ptr variable, just like in java
    mainlist = ['mainlist', 11,13]
  def usingGlobal():
    global globalvar; # needed. make globalvar a module-level ptr, so as to reseat it
    globalvar = ('globalvar', 11)
    
  mainlist=alias231=['mainlist', 8,5,2]
  print mainlist, '= orginal'
  broken1()
  print mainlist, 'after broken1(), the local var is unaffected'
  assert id(alias231)==id(mainlist)
  
  global globalvar; # needed
  globalvar=alias97=('globalvar', 2,3,5,7)
  usingGlobal()
  print globalvar
  assert id(alias97) != id(globalvar)
  
main()