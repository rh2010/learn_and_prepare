#! /usr/bin/env python

#
# Implement program for permutation, recursive and iterative.
#
def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n-1)

    # End factorial

def swap(one, two):
    return two, one
    # End swap()

def perm(string):
    length = len(string)
    count = factorial(length)
    print("String length: %d, count: %d" % (length, count))

    i = 0
    j = 1
    m = 0

    while (i < count):
        perm = string

        k = 0
        while (k != count/length):
            while (j != length-1):
                # print the permutation
                print("%s" % ("".join(perm)))

                # swap perm[j] and perm[j+1]
                perm[j], perm[j+1] = perm[j+1], perm[j]

                j = j + 1
                k = k + 1
                i = i + 1
            # outer while
            j = 1

        m = m + 1
        if (m == length):
            break

        # swap perm[0] and perm[m]
        perm[0], perm[m] = perm[m], perm[0]
    # End of Iterative permutation.

def recursive_perm(string, start, end):
    #print("Str: %s, start: %d, end: %d\n" % ("".join(string), start, end))

    if (start == end):
        print ("%s" % ("".join(string)))
        return

    for index in range(start, end+1):
        #print ("index: %d" % (index))
        # swap
        string[start], string[index] = string[index], string[start]
        recursive_perm(string, start+1, end)
        # swap back
        string[start], string[index] = string[index], string[start]

    # End of recursive_perm

if __name__ == "__main__":
    string = "abcd"
    test_string = list(string)

    # Iterative permutations
    perm(test_string)

    # Recursive permutations
    recursive_perm(test_string, 0, len(test_string) - 1)

    # End of Main.
