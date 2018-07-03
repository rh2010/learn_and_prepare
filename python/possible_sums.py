#!/usr/bin/python3
'''
Possible Sums problem:

You have a collection of coins, and you know the values of the coins and the quantity of each type of coin in it. You want to know how many distinct sums you can make from non-empty groupings of these coins.

Example

For coins = [10, 50, 100] and quantity = [1, 2, 1], the output should be
possibleSums(coins, quantity) = 9.

Here are all the possible sums:

50 = 50;
10 + 50 = 60;
50 + 100 = 150;
10 + 50 + 100 = 160;
50 + 50 = 100;
10 + 50 + 50 = 110;
50 + 50 + 100 = 200;
10 + 50 + 50 + 100 = 210;
10 = 10;
100 = 100;
10 + 100 = 110.
As you can see, there are 9 distinct sums that can be created from non-empty groupings of your coins.
'''

def possibleSums(coins, quantity):
    maximum = sum((map(lambda t: t[0] * t[1], zip(coins, quantity))))

    print(maximum)
    dp = [False] * (maximum + 1)
    dp[0] = True
    print(dp)
    for coin,q in zip(coins,quantity):
        print("[%d : %d]" % (coin, q))
        for b in range(coin):
            num = -1
            for i in range(b,maximum+1,coin):
                print(i, end=' ')
                if dp[i]:
                    print("Re-setting num to 0")
                    num = 0
                elif num>=0:
                    num += 1
                dp[i] = 0 <= num <= q
                if dp[i] is True:
                    print("Setting %d to True\n" % (i))
            print()
    return (sum(dp) - 1)


if __name__ == "__main__":
    n = possibleSums([10, 50, 100], [1, 2, 1])
    #n = possibleSums([1, 2, 3], [1, 2, 2])
    print("result: %d\n" % (n))
