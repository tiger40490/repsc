class Node(object):
    def __init__(self, data, next_node=None):
        self.data = data
        self.next = next_node
_7 = Node(7)
_6 = Node(6, _7)
_5 = Node(5, _6)
_4 = Node(4, _5)
_3 = Node(3, _4)
_2 = Node(2, _3)
_1 = Node(1, _2)
root = _1
### above is reusable set-up

def dump(limit=99):
    node = root
    count=0
    while(1):
        if node is None:
            print 'end'
            break
        print node.data, '->',
        count += 1
        if count >= limit:
            print '... list too long, perhaps due to loop'
            break
        node = node.next
def findLoopByReversing():
    global root #otherwise, compiler gives misleading errors
    originalRoot = root
	
    pre = root
    me = root    
    while(1):
        ne = me.next
        if ne is originalRoot:
            print 'at', me.data, ', link points to originalRoot'
            return True
        me.next = pre;print me.data, '<- link fixed internally'
        if ne is None: # exit condition
            root.next = None
            root = me
            return False
        pre = me
        me = ne
		
def main():
    #_7.next = _7 # create a loop at tend of the list, where #7 points to itself.
    _7.next = _3 # create a loop where #7 points back to #3.
    dump()
    isLooping = findLoopByReversing()
    if not isLooping: dump()
    else: print 'original list has loop, but the modified list is now messed up'

main()
