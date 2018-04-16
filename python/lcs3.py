#!/usr/bin/python3

import sys
def get_array(a, b, c):
    return [[[0 for _ in range(c)] for _ in range(b)] for _ in range(a)]

def lcs3(a, b, c):
    #write your code here
    a_len = len(a)
    b_len = len(b)
    c_len = len(c)

    if a_len == 0 or b_len == 0 or c_len == 0:
        return 0

    l = get_array(a_len+1, b_len+1, c_len+1)

    for i in range(1,a_len+1):
        for j in range(1,b_len+1):
            for k in range(1,c_len+1):
                if a[i-1] == b[j-1] and a[i-1]== c[k-1]:
                    l[i][j][k] = l[i-1][j-1][k-1] + 1
                else:
                    l[i][j][k] = max(max(l[i-1][j][k], l[i][j-1][k]), l[i][j][k-1])

    return l[a_len][b_len][c_len]

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    an = data[0]
    data = data[1:]
    a = data[:an]
    data = data[an:]
    bn = data[0]
    data = data[1:]
    b = data[:bn]
    data = data[bn:]
    cn = data[0]
    data = data[1:]
    c = data[:cn]
    print(lcs3(a, b, c))
