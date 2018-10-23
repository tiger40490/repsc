#!/usr/bin/env python
comboLen=3
pool=tuple(sorted(['b', 'c', 'e', 'd', 'a']))
combos=['']   
def add1charToEachCombo():
    global combos
    newCombos=[]
    for combo in combos:
        for char in pool:
            newCombos.append(combo + char)
        
    combos = newCombos
    print '--', len(combos), combos
        
def main():
    for _ in xrange(comboLen):
        add1charToEachCombo()
main()
'''Requirement: given 5 distinct chars, generate all combinations
of 3 chars by redrawing, ideally in ascending order
'''
