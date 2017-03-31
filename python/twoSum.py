#! /usr/bin/env python

import os
import sys
import time
import re


def twoSum(arr, num):
    hashmap = {}

    idx1 = 0
    idx2 = 0

    for val in arr:
        temp = num - val

        if temp in hashmap.keys():
            print("%d, %d\n" % (temp, val))
            idx1 = temp
            idx2 = val
        else:
            hashmap.update({val:val})

    return idx1, idx2



    ## End twoSum

if __name__ == "__main__":
    arr = [1, 4, 45, 6, 10, -8]
    num = 16

    idx1, idx2 = twoSum(arr, num)

    print("Index is: %d, %d\n" % (idx1, idx2))

    ## End main
