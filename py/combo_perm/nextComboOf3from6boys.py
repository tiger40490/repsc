'''Req: generate in ascending order all 3-combos of 6 distinct chars. We should get 6C3 = 20 combos

Plan: First generate 6C2=15 combos. For each combo (arranged as sorted string), 
we only append a single Higher character. Many of the 15 combos are discarded 
-- inefficient, but simple
'''
