#!/usr/bin/python3

#
# Runtime: log(ab)
#
def gcd(a, b):
    if b == 0:
        return a
    c = a%b
    return gcd(b, c)

def lcm(a, b):
    g_c_d = gcd(a, b)
    print("GCD : %d" % g_c_d)
    x = a/g_c_d

    print("x: %u" % x)
    l_c_m = long(x*b)
    
    print("x * b: %u" % l_c_m)
    return l_c_m

if __name__ == "__main__":
    a = int(input())
    b = int(input())
    print("LCM: %d" % (lcm(a, b)))
