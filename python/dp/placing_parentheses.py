# Uses python3

'''
Implement a routine to find out the appropriate place for placing
parentheses so that a given arithmetic operation evaluates to it's
maximum possible value
For eg:
1. 5-8+7*4-8+9 => 200
2. 1+2-3*4-5   => 6
3. 1+5         => 6
'''
def evalt(a, b, op):
    if op == '+':
        return int(a) + int(b)
    elif op == '-':
        return int(a) - int(b)
    elif op == '*':
        return int(a) * int(b)
    else:
        assert False

def min_and_max(i, j, expr, Min, Max):
    minimum = 99999
    maximum = -99999

    for k in range(i, j):
        print("k: %d" % (k))
        print("i:k [%d][%d]  k+1, j [%d][%d]" % (i, k, k+1, j))
        op = expr[(2*k)+1]
        print(op)
        a = evalt(Max[i][k], Max[k+1][j], op)
        b = evalt(Max[i][k], Min[k+1][j], op)
        c = evalt(Min[i][k], Max[k+1][j], op)
        d = evalt(Min[i][k], Min[k+1][j], op)
        print(a, b, c, d)
        maximum = max(max(max(maximum, a), max(b, c)), d)
        minimum = min(min(min(minimum, a), min(b, c)), d)

    print("[%d][%d]: %d:%d" % (i, j, minimum, maximum))
    return (minimum, maximum)

def get_maximum_value(dataset):
    # digits at even positions
    # ops at odd positions
    print(dataset)

    size = int(len(dataset)/2)

    print("Size: %d, len: %d" % (size, len(dataset)))

    Min = [[0 for _ in range(size+1)] for _ in range(size+1)]
    Max = [[0 for _ in range(size+1)] for _ in range(size+1)]

    '''
    Init Min and Max
    '''
    for i in range(size+1):
        Min[i][i] = dataset[2*i]
        Max[i][i] = dataset[2*i]

    print("Min")
    print(Min)
    print("Max")
    print(Max)
    for s in range(1, size+1):
        print("Range: %d" % (s))
        for i in range(size+1-s):
            j = i+s
            print("\t[%d][%d]" % (i, j))
            Min[i][j], Max[i][j] = min_and_max(i, j, dataset, Min, Max)
            print("Min")
            print(Min)
            print("Max")
            print(Max)

    #write your code here
    return Max[0][size]


if __name__ == "__main__":
    print(get_maximum_value(input()))
