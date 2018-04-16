#!/usr/bin/python3

#
# Longest Common subsequence
#
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
