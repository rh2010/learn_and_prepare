# Uses python3
import sys

def dp_sequence(n):
    l = [0]*(n+1)
    num = [0]*(n+1)

    l[0] = 0
    num[0] = 0

    l[1] = 0
    num[1] = 0
    #l[2] = 1
    #l[3] = 1

    for i in range(1, n+1):
        if i == 1:
            continue

        t1 = l[i-1] + 1
        min_val = t1
        choice = i-1

        if i % 3 == 0:
            # divisible by 3
            t3 = l[int(i/3)] + 1
            min_val = min(min_val, t3)
            if min_val == t3:
                choice = int(i/3)
        
        if i%2 == 0:
            # divisible by 2
            t2 = l[int(i/2)] + 1
            min_val = min(min_val, t2)
            if min_val == t2:
                choice = int(i/2)

        l[i] = min_val
        num[i] = choice

    # build the sequence in reverse order
    seq = []
    temp = n
    while temp > 0:
        seq.append(temp)
        temp = num[temp]

    seq.reverse()
    #print()
    #print(l)
    #print(num)
    #print(seq)
    #print(l)
    return seq

def optimal_sequence(n):
    sequence = []
    while n >= 1:
        sequence.append(n)
        if n % 3 == 0:
            n = n // 3
        elif n % 2 == 0:
            n = n // 2
        else:
            n = n - 1
    return reversed(sequence)

input = sys.stdin.read()
n = int(input)
#sequence = list(optimal_sequence(n))
#print(len(sequence) - 1)
#for x in sequence:
#    print(x, end=' ')
#
#print("DP: %d" % (dp_sequence(n)))
sequence = list(dp_sequence(n))
print(len(sequence) - 1)
for x in sequence:
    print(x, end=' ')

print()
