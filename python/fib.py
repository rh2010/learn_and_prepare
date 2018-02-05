#!/usr/bin/python3

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

if __name__ == "__main__":
    val = int(input("Enter: "))
    print("fib[%d] : %d" % (val, fib(val)))
