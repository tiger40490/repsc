# Q: what integrated test cases are more "effective" at testing multiple message types?

A: I feel the Cxl i.e. Decrement test is very good. Such a test requires the AddOrder message be saved, and then look-up, then quantity subtraction.

A: Before a Cxl, it's also effective to send a Exe on the same order, as it also requires order look-up and quantity decrement.

A: Before the Exe, it's also effective to send a Rep. This requires look-up.

# -- OOS scenario in integration test --
I sent Packet #1 #2 #5 #4 #3

Packets #5 and #4 are warehoused. When #3 gets parsed, parser looks for #4 in the warehouse and parses it. Then parser looks for #5.

# -- OOS scenario in simple test --
My main.cc also shows a simple test scenario #1 #2 #11 #8 #15 #13 #15

This test scenario is designed to test all OOS edge cases. More thorough than the ingegration test, without the complexities of message parsing.