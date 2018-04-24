# Uses python3
import sys
import itertools

def get_array(row, column):
    return [[0 for _ in range(column)] for _ in range(row)]

def get_knapsack(W, l, result):
    length = len(l)

    # start from the end
    i = length
    j = W
    
    res = []
    # Note: the weights and value are same.
    while i>0 and j>0:
        curr = result[i][j]

        not_used = result[i-1][j] # is the current element is not used
        used = result[i-1][j-l[i-1]] # is the current is used

        #print("[%d][%d] : curr: %d, used: %d, not_used %d" % (i, j, curr, used, not_used))
        if curr == not_used:
            # this value was not used.
            #print("\tNot using %d" % (l[i-1]))
            i = i-1
        elif curr == used+l[i-1]:
            #print("\tUsing %d" % (l[i-1]))
            res.append(l[i-1])
            j = j - l[i-1]
            i = i-1
        else:
            pass
            #print("Error")

    #print("Knapsack")
    #print(res)
    return res

def knapsack(W, w):
    # write your code here
    n = len(w)
    if n is 0:
        return 0

    result = get_array(n+1, W+1)

    #
    #
    for i in range(1, n+1):
        #print("Wi: %d" % (w[i-1]))
        for x in range(W+1):
            if x >= w[i-1]:
                result[i][x] = max(result[i-1][x], (result[i-1][x-w[i-1]]+w[i-1]) )
            else:
                result[i][x] = result[i-1][x]
            #print("[%d][%d]: %d" % (i, x, result[i][x]))

    #print(result)
    # build the list of items included in the knapsack and return that instead.
    return get_knapsack(W, w, result)
    #return result[n][W]

def partition3(A):
    total = sum(A)

    if total%3:
        return 0

    goal = int(total/3)
    #print("Goal: %d" % (goal))

    '''
    Sort in decreasing order.
    some corner cases are addressed by this.
    For eg:
        1, 1, 1, 2, 2, 2
        This will fail if we don't sort in the decreasing order.
    '''
    A.sort()
    A.reverse()

    B = A
    result = []
    i = 3
    while i > 0:
        res = knapsack(goal, A)

        if goal != sum(res):
            return 0

        # the list res has the elements which is the first set
        result.append(res)

        # remove res from A
        for x in res:
            A.remove(x)
        i = i-1

    # the above loop will run three times.

    # there should be no items remaining in A
    if len(A) is 0:
        return 1

    return 0
    #result.append(A)
    #print(result)
    # if the sum of elements remaining in A is the same as goal, then,
    # we are able to successfully partition the array in 3 equal parts
    # else, no.
    #if goal == sum(A):
    #    return 1
    #else:
    #    return 0

if __name__ == '__main__':
    input = sys.stdin.read()
    n, *A = list(map(int, input.split()))
    print(partition3(A))

