#!/usr/bin/python3

'''
def fib(n):
    n_minus_one = 1
    n_minus_two = 0

    if n == 0:
        return 0

    if n == 1:
        return 1

    for i in range(2, n+1):
        f = n_minus_one + n_minus_two
        n_minus_two = n_minus_one
        n_minus_one = f

    return f
'''

def fib2(n):
    '''
    Print the Fibonacci sequence till 'n'th Fibonacci number.
    Return the 'n'th Fibonacci number.
    '''
    n_1 = 1 # n is 1
    n_2 = 0 # n is 0

    res = 0

    if n == 0:
        return n_2
    print (n_2)

    if n == 1:
        return n_1
    print (n_1)

    for i in range(2, n+1):
        f = n_1 + n_2
        n_2 = n_1
        n_1 = f
        print ("%d " % f)

    return f
    # End fib2

if __name__ == "__main__":
    val = int(input("Enter: "))
    #print("fib[%d] : %d" % (val, fib(val)))
    print("fib[%d] : %d" % (val, fib2(val)))
