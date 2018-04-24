#!/usr/bin/python3
def canPartition(nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    total = sum(nums)
    if total%2:
        return False
    
    goal = int(total/2);
    
    res = [[False for _ in range(goal+1)] for _ in range(len(nums)+1)]
    
    for i in range(len(nums)+1):
        res[i][0]=True
        
    for i in range(1,len(nums)+1):
        for j in range(1, goal+1):
            if j == nums[i-1]:
                res[i][j] = True
            else:
                rem =  j-nums[i-1]
                if rem > 0:
                    if res[i-1][j] or res[i-1][rem]:
                        res[i][j] = True
                    
                        
    return res[len(nums)][goal]   

if __name__=="__main__":
    arr = [43,42,20,86,5,5,64,77,92,94,7,4,28,42,67,97,93,85,53,41,22,86,26,45,100,57,19,94,83,29,36,100,24,36,62,38,97,86,10,86,76,69,73,31,53,95,82,88,72,29,96,24,90,33,62,85,63,93,83,20,23,72,26,31,97,79,72,69,38,29,36,75,73,66,48,50,77,12,79,48,3,67,16,40,11,79,28,5,18,12,80,4,82,60,29,96,95,2,50,99]
    print(canPartition(arr))
