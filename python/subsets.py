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

if __name__=="__main__":
    s = list(raw_input())
    #print(s)
    subsets(s)
