Given, abcde, How many combinations of 3? 5-choose-3 = 10 standard formula, but let’s implement in c++.

It’s useful to define a score for a combination — sort the combination into a string. The string is the score. Now,

Q1: generate all combinations@3 from 5 distinct chars, in ascending score.

Q2 (more importantly) given any combination of 3, generate the next higher combination of 3.  Output each combination as a sorted string to keep things clean. Extremely effective constraint and simplification.
