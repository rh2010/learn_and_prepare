# Uses python3
import sys

'''
Knapsack Problem:
    Implementation of a dynamic programming solution of the
    knapsack problem.
'''
def get_array(row, column):
    return [[0 for _ in range(column)] for _ in range(row)]

def optimal_weight(W, w):
    # write your code here
    n = len(w)
    if n is 0:
        return 0

    result = get_array(2, W+1)

    #
    # Theese commented out solutions uses more memory.
    #
    #for i in range(1, n+1):
    #    #print("Wi: %d" % (w[i-1]))
    #    for x in range(W+1):
    #        if x >= w[i-1]:
    #            result[i][x] = max(result[i-1][x], (result[i-1][x-w[i-1]]+w[i-1]) )
    #        else:
    #           result[i][x] = result[i-1][x]
    #        #print("[%d][%d]: %d" % (i, x, result[i][x]))

    #for i in range(1, n+1):
    #    print("Wi: %d" % (w[i-1]))
    #    for x in range(1, W+1):
    #        result[i][x] = result[i-1][x]
    #        if x >= w[i-1]:
    #            res = result[i-1][x-w[i-1]] + w[i-1]
    #            if result[i][x] < res:
    #                result[i][x] = res
    #            #result[i][x] = max(result[i-1][x], (result[i-1][x-w[i-1]]+w[i-1]) )
    #        print("[%d][%d]: %d" % (i, x, result[i][x]))

    #
    # More faster and uses less memory
    curr = 0
    prev = 1
    for x in w:
        # swap prev and curr
        prev, curr = curr, prev
        for p in range(1, W+1):
            if p >= x:
                result[curr][p] = max(result[prev][p], result[prev][p-x]+x)
            else:
                result[curr][p] = result[prev][p]

    
    #return result[n][W]
    return result[curr][W]

if __name__ == '__main__':
    input = sys.stdin.read()
    W, n, *w = list(map(int, input.split()))
    print(optimal_weight(W, w))
