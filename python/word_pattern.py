#!/usr/bin/python3
import sys

'''
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:

pattern = "abab", str = "redblueredblue" should return true.
pattern = "aaaa", str = "asdasdasdasd" should return true.
pattern = "aabb", str = "xyzabcxzyabc" should return false. 
Notes:
You may assume both pattern and str contains only lowercase letters.
'''
def solve(pattern, string, hmap):
    pat_len = len(pattern)
    str_len = len(string)

    if pat_len is 0 and str_len is 0:
        return True

    if pat_len is 0 or str_len is 0:
        return False

    c = pattern[0]

    try:
        sub_string = hmap[c]
        sub_string_len = len(sub_string)
        if sub_string != string[0:sub_string_len]:
            return False
        return solve(pattern[1:], string[sub_string_len:], hmap)

    except KeyError:
        for i in range(str_len):
            hmap[c] = string[0:i+1]
            if solve(pattern[1:], string[i+1:], hmap) is True:
                return True
            del hmap[c] # backtrack

    return False

if __name__ == "__main__":
    argc = len(sys.argv)

    if argc < 3:
        print("usage: ./word_pattern.py <pattern string> <string>")
        print("eg: aba redblackred")
        exit()

    pattern = sys.argv[1]
    string = sys.argv[2]

    print("Pattern: %s" % pattern)
    print("String: %s" % string)

    hmap = dict()
    print("%s" % (solve(pattern, string, hmap)))

