#!/usr/bin/python3
'''
Given a string s , find the length of the longest substring t  that contains at most k distinct characters.

Example 1:

Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.
Example 2:

Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.
'''
def lengthOfLongestSubstringKDistinct(s, k):
    result = 0
    sl = len(s)
    if sl is 0:
        return result

    begin = 0
    end = 0
    d = 0
    k = 2
    
    table = dict()
    
    while end < sl:
        c = s[end]
        
        if c in table:
            table[c] += 1
            if table[c] == 1:
                d += 1
        else:
            table[c] = 1
            d += 1
        
        end += 1
        
        if d > k:
            f = s[begin]
            
            table[f] -= 1
            if table[f] == 0:
                d -= 1
                
            begin += 1
            
        if end-begin > result:
            result = end-begin
            
    return result

if __name__=="__main__":
    s = "eceba"
    s1 = "ccaabbb"
    k = 2
    print(lengthOfLongestSubstringKDistinct(s, k))
    print(lengthOfLongestSubstringKDistinct(s1, k))
