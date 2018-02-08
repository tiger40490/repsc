'''Req: generate in ascending order all 2-combos of 6 distinct chars.

There are 6C3 = 20 combos

Plan: First we generate 6C2=15 combos. For each combo (arranged as sorted string), 
we only append a single higher character.
'''
