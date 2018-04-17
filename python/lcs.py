#!/usr/bin/python3

#
# Longest Common subsequence
#

def lcs_string(a, b, l):
    '''
    After calculating lcs matrix 'l', we can
    use it to print the lcs string.
    This is a helper routine to do that.
    '''
    a_len = len(a)
    b_len = len(b)

    res = []
    i = a_len
    j = b_len

    while i > 0 and j > 0:
        if a[i-1] == b[j-1]:
            #
            res.append(a[i-1])
            i = i-1
            j = j-1
        else:
            # not equal case
            upper = l[i-1][j]
            left = l[i][j-1]

            if upper == left:
                i = i-1
            elif upper > left:
                i = i-1
            else:
                j = j-1

    res.reverse()
    print(res)
    return res

def lcs(a, b):
    a_len = len(a)
    b_len = len(b)

    l = []
    for i in range(a_len+1):
        l.append(([0]*(b_len+1)))

    for i in range(1,a_len+1):
        for j in range(1,b_len+1):
            if a[i-1] == b[j-1]:
                l[i][j] = l[i-1][j-1] + 1
            else:
                l[i][j] = max((l[i-1][j]), (l[i][j-1]))


    return l[a_len][b_len]

if __name__ == "__main__":
    a = input()
    b = input()

    print("\n")
    print(a)
    print(b)
    print("LCS: %d" % (lcs(a, b)))
