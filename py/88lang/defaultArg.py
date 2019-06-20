def append_to(element, to=[]):
    to.append(element)
    print to
    return to

my_list = append_to(12)
list2 = append_to(42) # prints [12, 42]!

assert my_list is list2 # q[is ] explained in https://stackoverflow.com/questions/2987958/how-is-the-is-keyword-implemented-in-python
assert id(my_list) == id(list2)
'''Unexpected behavior of python default argument
 
based on https://docs.python-guide.org/writing/gotchas/
'''