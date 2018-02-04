'''Requirement: given 5 distinct chars, generate all combinations of 3 chars by redrawing.
I think there shoudl be 5^3 answers

Once we have a combo, how do we generate the next combo?
Start from right most and try to "increment" it. This would be an iterative algo
'''

comboLen=3
pool=sorted(['b', 'c', 'e', 'd', 'a'])
combos=[]
def dump():
    print len(combos), combos
def add1charToEachCombo():
    global combos
    if not combos:
        for char in pool:
            combos.append(char)
        return
    newCombos=[]
    for combo in combos:
        for char in pool:
            new = combo
            new+= char
            newCombos.append(new)
        
    combos = newCombos
        
def main():
    for layer in xrange(comboLen):
        add1charToEachCombo()
        print '-- after add1charToEachCombo --'
        dump()

main()
    
    
    
