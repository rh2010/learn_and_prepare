#! /usr/bin/env python
import sys

#
# Given a list of strings, write a function to sort / re-arrange the
# list in such a way that anagrams get grouped together.
#

#
# this routine will be effective only if all the characters in each
# string are unique.
#
# If there are duplicate characters in the string then the hashing algorithm
# does not work well.
#
#
def calc_hash(word):
    res = 0

    for c in word:
        res = res ^ ord(c)

    print("Word: %s, hash: %d" % (word, res))
    return res
    # End calc_hash()

def group_anagrams(str_list):
    print ("Input: \n%s" % str_list)
    sort_dict = {}
    word_hash = 0
    ana_sorted_list = []

    for word in str_list:
        word_hash = calc_hash(word)

        print("Adding: %s" % (word))
        try:
            ana_list = sort_dict[word_hash]

            # something already exists in the list for this hash, update it
            print("Not first time")
            ana_list.append(word)
            sort_dict.update({word_hash:ana_list})
        except KeyError:
            # first time, just add a one element list
            print("First time")
            ana_list = [word]
            sort_dict.update({word_hash:ana_list})

        print("Updated sort_dist: %s" % (sort_dict))

    for key in sort_dict.keys():
        l = sort_dict[key]
        ana_sorted_list = ana_sorted_list + l

    return ana_sorted_list
    # End anagram_sort()

if __name__ == "__main__":
    argc = len(sys.argv)

    string_list = sys.argv[1:]

    anagram_sorted_list = group_anagrams(string_list)

    print("The sorted list: \n%s" % (anagram_sorted_list))
