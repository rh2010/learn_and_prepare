#!/usr/bin/python

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
        if start_index > 1 and (prefix_sum[start_index-1] == prefix_sum[start_index]):
            if end != -1:
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

