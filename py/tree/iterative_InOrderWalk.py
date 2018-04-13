class Node(object):
    def __init__(self, data, left_node=None, right_node=None):
        self.data = data
        self.le = left_node
        self.ri = right_node
'''   5
  2       7
 1 3        8
             9
'''
_9=Node(9)
_8=Node(8, None, _9)
_7=Node(7, None, _8)
_3=Node(3)
_1=Node(1)
_2=Node(2, _1, _a)
_5=Node(5, _2, _7) 
root = _5

def visit(node):
    if node is None: return
    if node.le: visit(node.le)
    print node.data
    if node.ri: visit(node.ri)
        
def inOrderDftRecursive():
    visit(root)
    
def main():
    inOrderDftRecursive()

main()