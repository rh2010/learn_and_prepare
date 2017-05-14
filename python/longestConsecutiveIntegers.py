#! /usr/bin/env python

import os
import sys

def longest_consecutive_integer_sequence(arr):
    print("Input: %s" % (arr))
    hashmap = {}
    index = 0
    prev = 0
    count = 0
    max_count = 0
    done = False 
    
    for x in arr:
        done = False
        count = 1
        prev = x - 1
        n = x + 1

        while not done:
            try:
                y = hashmap[prev]
                count = count + 1
                prev = prev - 1
            except KeyError:
                done = True

        done = False
        while not done:
            try:
                y = hashmap[n]
                count = count + 1
                n = n + 1
            except KeyError:
                done = True
       
        hashmap.update({x:index})
        index = index + 1
        max_count = max(count, max_count)
        #print("Index: %d, max_count: %d" % (index, max_count))
 
    return max_count
    # End function

if __name__ == "__main__":
    length = 0
    #arr = [4, 3, 10, 2, 7]
    arr = [4, 100, 40, 11, 3, 7, 2, 1, 44, 8, 111, 6]
    #size = len(sys.argv)
    #args = sys.argv[1:]

    #print args

    #if size < 2:
    #    print "Not enough arsuments"
    #    exit()

    #arr = map(int, args.split())

    #size = len(args)
    #for ele in args:
    #    #arr = arr.extend(int(ele))
    #    arr = arr.append(int(ele))

    length = longest_consecutive_integer_sequence(arr)
    print("Longest consecutive integer subarray size is: %d" % (length))
