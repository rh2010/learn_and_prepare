#!/usr/bin/python

'''
Print all n! subsets of the input set 's'
'''
def print_subsets(r, s):
    if len(s) is 0:
        print(r)
        return

    print_subsets(r+s[0], s[1:])
    print_subsets(r, s[1:])
    return

def subsets(s):
    print_subsets("", s)
    return

def do_subsets_2(s, powerset, ss, start):
    powerset.append(''.join(ss))
    #print(ss)

    for i in range(start, len(s)):
        ss.append(s[i])
        do_subsets_2(s, powerset, ss, i+1)
        ss.pop()

def subsets_2(s):
    powerset = []
    ss = []
    do_subsets_2(s, powerset, ss, 0)

    return powerset

def do_subsets_dup(s, powerset, ss, start):
    powerset.append(''.join(ss))

    for i in range(start, len(s)):
        if i > start and s[i] == s[i-1]:
            continue
        ss.append(s[i])
        do_subsets_dup(s, powerset, ss, i+1)
        ss.pop()

def subsets_dup(s):
    powerset = []
    ss = []
    s.sort()
    do_subsets_dup(s, powerset, ss, 0)

    return powerset

if __name__=="__main__":
    s = list(raw_input())
    #print(s)
    subsets(s)

    # Subsets method 2.
    print(subsets_2(s))
    #subsets_2(s)

    s2 = list(raw_input())
    # Subsets with duplicates
    print(subsets_dup(s2))
