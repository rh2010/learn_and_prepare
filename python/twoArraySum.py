#! /usr/bin/env python

import os
import sys
import time

def twoArraySum(arr1, arr2, val):
    list_pairs = []
    hashmap = {}

    # take all the elements in arr1 and put them in the hashmap
    print("Buidling the hash from arr1")
    idx = 0
    for element in arr1:
        hashmap.update({element:idx})
        idx = idx + 1
    
    print("Hashmap of arr1:\n%s" % (hashmap))

    idx = 0
    for element in arr2:
        diff = val - element
        try:
            idx = hashmap[diff]
            list_pairs.append([element, diff])
        except KeyError:
            print("Value %d, not in hashmap" % (diff))
    
    return list_pairs
    # End of twoArraySum

if __name__ == "__main__":
    arr1 = [10, 1, 33, 45, 11, 17, 20]
    arr2 = [40, 15, -1, 101, -4, 5]

    sum_val = 16

    print("Input:\narr1: %s\narr2: %s\nSum: %d" % (arr1, arr2, sum_val))

    list_pairs = twoArraySum(arr1, arr2, sum_val)

    print("List of pairs that sum to %d are %s" % (sum_val, list_pairs))
    # End of main
