Q: what integrated test cases are more "effective" at testing multiple classes?

A: I feel the Cxl i.e. Decrement test is very good. Such a test requires the AddOrder message be saved, and then look-up, then quantity subtraction.

A: Before a Cxl, it's also effective to send a Exe on the same order, as it also requires order look-up and quantity decrement.

A: Before the Exe, it's also effective to send a Rep. This requires look-up.
