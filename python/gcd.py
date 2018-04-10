#!/usr/bin/python3

#
# Runtime: log(ab)
#
def gcd(a, b):
    if b == 0:
        return a
    c = a%b
    return gcd(b, c)

if __name__ == "__main__":
    a = int(input())
    b = int(input())
    print("GCD: %d" % (gcd(a, b)))
