# showcase omit main(), to maximize screen real estate
def failed_to_add(myset, digit): # return False when failed
    return digit == 0 or len(myset) == ( myset.add(digit) or len(myset))
def other_number_failed(myset, num): # returns False by default if everything good
    for digit in(num/100, num/10%10, num%10):
        if failed_to_add(myset, digit):     return True
def check(number1, myset):
    number2 = 2*number1
    if other_number_failed(myset, number2): return 
    number3 = 3*number1
    if other_number_failed(myset, number3): return 
    print number1, number2, number3, myset
    winners.append([number1, number2, number3])

winners=list()
nine_digits = tuple(range(1,10))
for digit1 in (1,2,3):
    last8 = list(nine_digits)
    last8.remove(digit1)
    for digit2 in last8:
        last7 = list(last8)
        last7.remove(digit2)
        for digit3 in last7:
            number1 = digit1*100 + digit2*10 + digit3
            if number1 > 329: break
            check(number1, {digit1, digit2, digit3})
print "-- lucky winners --", winners

'''Q: Find three 3-digit numbers with a ratio of 1:2:3. These numbers pick their 3 digits from a range of 1 to 9. You must use up all distinct 9 digits. For example, a set of 123:246:369 doesn't qualify.

See My blog https://wp.me/p74oew-2GP 
'''