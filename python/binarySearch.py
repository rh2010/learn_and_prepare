#! /usr/bin/env python

#
# Binary Search:
# Given a sorted array and a key, find the key in the sorted array.
# If found:
#   return the index of the key in the array
# else:
#   return the index in which the key can be inserted.
#
def binary_search_i(a, low, high, key):
    mid = -1

    while low <= high:
        mid = low + (high-low)/2
        if (a[mid] == key):
            break
        elif key < a[mid]:
            high = mid-1
        else:
            low = mid+1

    if (high < low):
        return low

    return mid

def binary_search_r(a, low, high, key):
    if (high < low):
        return low

    mid = low + (high-low)/2

    if a[mid] == key:
        return mid
    elif key < a[mid]:
        return binary_search_r(a, low, mid-1, key)
    else:
        return binary_search_r(a, mid+1, high, key)


if __name__ == "__main__":
    arr = [3, 5, 8, 10, 12, 15, 18, 20, 20, 50, 60]
    print(arr)

    key =0
    while key != -1:
        key = int(input("Key: "))

        print("Index[R]: %d" % binary_search_r(arr, 0, len(arr)-1, key))
        print("Index[I]: %d" % binary_search_i(arr, 0, len(arr)-1, key))
