import sys, os; from pprint import pprint
sys.stdout = os.fdopen(sys.stdout.fileno(), ‘w’, 0) # worked
pprint({1:'j', 3+2:'a'}); sys.exit()

'''This is a template for timed online tests. It saves screen real estate
'''