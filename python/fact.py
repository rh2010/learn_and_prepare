#!/usr/bin/python3

def fact(n):
    factorial = 1

    for i in range(1, n+1):
        factorial *= i

    return factorial
    # End fact

if __name__ == "__main__":
    val = int(input("Enter: "))
    print("factorial(%d): %d" % (val, fact(val)))
