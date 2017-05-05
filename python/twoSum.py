#! /usr/bin/env python

import os
import sys
import time
import re


#
# Return two lists
#   - First list contains all the pairs which sum equals to 'num'
#   - Second list contains index of all the pairs which sum equals to 'num'
#
def twoSum(arr, num):
    hashmap = {}
    index_list = []
    pairs_list = []

    print("List: %s, sum to: %d" % (arr, num))

    idx = 0
    for val in arr:
        temp = num - val

        try:
            index = hashmap[temp]
            # if temp is present in the hash then temp and val are the two
            # values whose sum is equal to 'num'
            index_list.append([index, idx])
            pairs_list.append([temp, val])
        except KeyError:
            hashmap.update({val:idx})

        idx = idx + 1

        #if temp in hashmap.keys():
        #    print("%d, %d\n" % (temp, val))
        #    idx1 = temp
        #    idx2 = val
        #else:
        #    hashmap.update({val:val})

    return index_list, pairs_list



    ## End twoSum

if __name__ == "__main__":
    arr = [1, 4, 45, 6, 10, -8]
    num = 16

    list_index, list_pairs = twoSum(arr, num)

    print("List of index: %s" % (list_index))
    print("List of pairs: %s" % (list_pairs))

    ## End main
