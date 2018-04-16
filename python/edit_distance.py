#!/usr/bin/python3

#
# edit distance of two strings
# 

def edit_distance(a, b):
    a_len = len(a)
    b_len = len(b)

    l = []

    for i in range(a_len+1):
        l.append(([0]*(b_len+1)))

    for i in range(1,a_len+1):
        l[i][0] = i

    for i in range(1,b_len+1):
        l[0][i] = i

    for i in range(1, a_len+1):
        for j in range(1, b_len+1):
            if a[i-1] == b[j-1]:
                l[i][j] = l[i-1][j-1]
            else:
                l[i][j] = min(l[i-1][j-1], min(l[i][j-1], l[i-1][j])) + 1

    return l[a_len][b_len]

if __name__ == "__main__":
    a = input()
    b = input()

    print(a)
    print(b)
    print("Edit Distance: %d" % (edit_distance(a, b)))
