#!/usr/bin/python3

def powRec(n, k):
    print("n(%d) : k(%d)\n" % (n, k))
    if (k == 0):
        return 1

    if (k%2 == 0):
        return powRec(n*n, k/2)
    else:
        return n * powRec(n, k-1)
    # End pow

def powIter(n, k):
    print("powIter: %d:%d" % (n, k))
    result = 1

    while (k > 0) :
        print("result(%d) : k(%d)\n" % (result, k))
        if (k & 1) :
            result = result * n

        k = k >> 1
        n = n * n

    print("result(%d) : k(%d)\n" % (result, k))
    return result
    # end powIter

def powIter2(n, k):
    print("powIter2: %d:%d" % (n, k))
    result = 1

    while (k > 0):
        print("n(%d) : k(%d)\n" % (result, k))
        if (k%2):
            result = result * n

        k = k//2
        n = n * n

    print("n(%d) : k(%d)\n" % (result, k))
    return result
    # End powIter2

if __name__ == "__main__":
    print("n raise to power k.")
    n = int(input("n: "))
    k = int(input("k: "))
    print("%d" % powRec(n, k))
    print("%d" % powIter(n, k))
    print("%d" % powIter2(n, k))
