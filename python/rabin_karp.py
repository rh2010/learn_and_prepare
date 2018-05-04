#!/usr/bin/python3

import sys

'''
Rabin Karp
    Implement Rabin Karp's pattern search algorithm.
'''

def strcmp(s1, s2):
    if len(s1) is not len(s2):
        return False

    i = 0

    while i < len(s1):
        if s1[i] != s2[i]:
            break
        i = i + 1

    if i != len(s1):
        return False
    return True

def get_prime_number():
    return 503

def poly_hash(pat, x, prime):
    size = len(pat)
    
    p_hash = 0
    i = 0

    for i in range(len(pat)):
        # for string, get the ascii value of the character
        a = ord(pat[i])
        p_hash = ((p_hash*x) + a)%prime

    return p_hash

def rabin_karp_search(pat, text):
    res = []

    if len(text) < len(pat):
        return res

    if len(text) == len(pat):
        if strcmp(text, pat):
            res.append(0)
        return res

    print("p_len: %d" % (len(pat)))
    print("t_len: %d" % (len(text)))

    p_size = len(pat)

    # get a big prime number, bigger than the max value of any element in the text
    prime = get_prime_number()
    print("prime: %d" % (prime))

    # a number between 1 and prime-1
    # for the sake of simplicity, let's keep it at 10
    x = 10

    # get the hash of the pattern
    p_hash = poly_hash(pat, x, prime)
    t_hash = poly_hash(text[:p_size], x, prime)

    print("p_hash: %d" % (p_hash))
    print(t_hash)

    if p_hash == t_hash:
        if strcmp(pat, text[:p_size]):
            res.append(0)

    # we need to pre-compute x^(p_size-1)
    r = 1
    for i in range(1, p_size):
        r = (r*x)%prime

    for i in range(1, len(text)-len(pat)+1):
        t_hash = (t_hash + prime - ((r*ord(text[i-1]))%prime) ) % prime
        t_hash = ((t_hash * x)%prime + ord(text[i+p_size-1]))%prime
        print("[%d] %d" % (i, t_hash))

        if p_hash == t_hash:
            if strcmp(pat, text[i:(i+p_size)]):
                res.append(i)


    return res

if __name__ == "__main__":
    argc = len(sys.argv)

    if argc is not 3:
        print("usage: ./string_search.py <pattern> <string>")
        exit()

    pattern = sys.argv[1]
    text = sys.argv[2]

    res = rabin_karp_search(pattern, text)

    print("Pattern found at: ", end=' ')
    for x in res:
        print("%d" % (x), end= ' ')
    print()
