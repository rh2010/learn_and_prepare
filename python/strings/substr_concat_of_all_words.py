#!/usr/bin/python3
'''
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input:
  s = "wordgoodstudentgoodword",
  words = ["word","student"]
Output: []
'''
def findSubstring(s, words):
    """
    :type s: str
    :type words: List[str]
    :rtype: List[int]
    """
    result = []
    sl = len(s)
    word_count = len(words)
    if word_count is 0:
        return result
    word_len = len(words[0])
    tgt = word_count * word_len
    #print(sl, word_count, word_len, tgt)
    
    # base case
    if sl < (word_count*word_len):
        return result
    
    table = dict()
    
    # initialize the table for alphabet count
    for word in words:
        try:
            count = table[word]
            table[word] += 1
        except KeyError:
            table[word] = 1

    '''
    We need to run this loop for word_len times, so, as to cover each
    character towards the end of the string.
    '''
    for i in range(word_len):
        #print("[%d]" % (i))
        ref = dict(table)
        end = i
        begin = i
        counter = len(ref)
        #print("\t%d\n\t%s" % (counter, ref))
        
        while end+word_len-1 < len(s):
            substr = s[end:end+word_len]
            #print("Eval: %s, (%d : %d), %s" % (substr, begin, end, s))
            
            if substr in ref:
                ref[substr] -= 1
                if ref[substr] == 0:
                    counter -= 1
                    
            end += word_len        
            #print("\t[%d]\n\t%s" % (end-begin, ref))
            if end-begin == (tgt):
                if counter == 0:
                    #print("Adding [%d] to result" % (begin))
                    result.append(begin)
                
                first_word = s[begin:begin+word_len]
                #print("begin - add back check for - %s" % (first_word))
                if first_word in ref:
                    ref[first_word] += 1
                    if ref[first_word] > 0:
                        counter += 1
                
                begin += word_len

    return result

if __name__=="__main__":
    s = "barfoothefoobarman"
    words = ["foo","bar"]
    print(findSubstring(s, words))
