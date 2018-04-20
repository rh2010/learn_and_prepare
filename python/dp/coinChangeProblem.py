#!/usr/bin/python3

'''
Problem Definition:
Given money amount 'm'
Find the minimum number of coins with denominations 1, 3, 4 that changes money.
'''

def get_largest_coin(money, coins):
    '''
    get the largest coin size amongst (1, 3, 4)
    which is greater than money
    '''
    for coin in reversed(coins):
        if money >= coin:
            return coin

def greedy_coin_change(m, coins):
    '''
    Use Greedy approach to solve coin change problem.
    '''
    change = []

    while m > 0:
        coin = get_largest_coin(m, coins)
        change.append(coin)
        m = m-coin

    return change

def getMinCoin(minCoin, m, coins):
    denomination = 0

    count = -1

    for coin in coins:
        if m >= coin:
            if count is -1 or minCoin[m-coin] + 1 < count:
                count = minCoin[m-coin] + 1
                denomination = coin
        else:
            break

    return count, denomination

def dp_coin_change(m, coins):
    '''
    Use Dynamic Programming approach to solve coin change problem.
    '''
    change = []
    minCoin = [0]*(m+1);

    for i in range(1, m+1):
        minCoin[i], coin = getMinCoin(minCoin, i, coins)

    return minCoin[m]

if __name__=="__main__":
    m = int(input())
    coins = [1, 3, 4]
    coins2 = [1, 5, 6]

    c = greedy_coin_change(m, coins2)
    print("Greedy:\n\t%d, %s" % (len(c), c))
    c2 = dp_coin_change(m, coins2)
    print("Optimal:\n\t%d" % (c2))
