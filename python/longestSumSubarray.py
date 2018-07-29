#!/usr/bin/python
'''
You have an unsorted array arr of non-negative integers and a number s.
Find a longest contiguous subarray in arr that has a sum equal to s.
Return two integers that represent its inclusive bounds.
If there are several possible answers, return the one with the smallest left bound. If there are no answers, return [-1].

Your answer should be 1-based, meaning that the first position of the array is 1 instead of 0.

Example

For s = 12 and arr = [1, 2, 3, 7, 5], the output should be
findLongestSubarrayBySum(s, arr) = [2, 4].

The sum of elements from the 2nd position to the 4th position (1-based) is equal to 12: 2 + 3 + 7.

For s = 15 and arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], the output should be
findLongestSubarrayBySum(s, arr) = [1, 5].

The sum of elements from the 1st position to the 5th position (1-based) is equal to 15: 1 + 2 + 3 + 4 + 5.

For s = 15 and arr = [1, 2, 3, 4, 5, 0, 0, 0, 6, 7, 8, 9, 10], the output should be
findLongestSubarrayBySum(s, arr) = [1, 8].

The sum of elements from the 1st position to the 8th position (1-based) is equal to 15: 1 + 2 + 3 + 4 + 5 + 0 + 0 + 0.

Input/Output

[execution time limit] 4 seconds (py3)

[input] integer s

The sum of the subarray that you are searching for.

Guaranteed constraints:
0 ≤ s ≤ 109.

[input] array.integer arr

The given array.

Guaranteed constraints:
1 ≤ arr.length ≤ 105,
0 ≤ arr[i] ≤ 104.

[output] array.integer

An array that contains two elements that represent the left and right bounds of the subarray, respectively (1-based).
If there is no such subarray, return [-1].
'''
def findLongestSubarrayBySum(s, arr):
    if len(arr) == 0:
        return [-1]

    prefix_sum = [0] * len(arr)

    prefix_sum[0] = arr[0]
    total = arr[0]

    if total >= s:
        index = 0
    else:
        index = -1
    for i,val in enumerate(arr[1:], start=1):
        total = total + val
        prefix_sum[i] = total
        if index == -1 and total >= s:
            index = i

    start_index = index
    start = -1
    end = -1
    init = -1
    #print(prefix_sum)

    while start_index < len(arr):
        #
        # case: if there is a zero at index 'start_index'
        #       that's the case when prefix_sum[start_index-1] will be equal
        #       to prefix_sum[start_index]
        #
        if start_index > 1 and (prefix_sum[start_index-1] == prefix_sum[start_index]):
            if end != -1:
                # extend the window by 1
                end += 1
            start_index += 1
            continue

        #print("S: %d, E: %d, init: %d" % (start, end, init))
        for i in range(init, start_index+1):
            if i == -1:
                a = prefix_sum[start_index]
            else:
                if arr[start_index] > s:
                    break
                a = prefix_sum[start_index]-prefix_sum[i]

            if a == s:
                #print("F: [%d : %d]" % (i, start_index))
                #if index == -1:
                #    init = i
                if (start_index-i) > (end-start) or start == -1:
                    start = i+2
                    end = start_index+1
                break
            elif a < s:
                init = i
                break
        start_index += 1

    if start == -1:
        return [-1]
    else:
        return start, end

if __name__ == "__main__":
    arr = [1,2,3,4,5,0,0,0,6,7,8,9,10]
    #arr = [1,2,3,4,5,0,0,0,6,7,8,9,10]
    s = 15
    print(arr)
    result = findLongestSubarrayBySum(s, arr)
    print(result)

