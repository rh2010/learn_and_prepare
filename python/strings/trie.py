#!/usr/bin/python3
import sys

'''
Problem Statement: Given a string of characters and a list of words (dictionary)
add spaces in the string at the right places so as to form the sentence.

Form a trie and use it to build words in the string and add spaces
'''
class TrieNode:
    c = None # the key
    word = False
    children = None

    def __init__(self, val):
        self.c = val
        self.word = False
        self.children = dict()

    def add_child(self, c):
        try:
            child = self.children[c]
            return child
        except KeyError:
            child = TrieNode(c)
            self.children.update({c:child})
            return child

    def get_child(self, c):
        try:
            child = self.children[c]
            return child
        except KeyError:
            return None

    def set_word(self):
        self.word = True

    def is_word(self):
        return self.word

class Trie:
    root = None
    def __init__(self, l=None):
        if l is not None:
            self.build(l)

    def build(self, list_of_strings):
        self.root = TrieNode('$') # special char for root node.

        for string in list_of_strings:
            curr = self.root
            for char in string:
                curr = curr.add_child(char)
                
            curr.set_word() # the current string ends here.

    def get_root(self):
        return self.root

    def show(self):
        curr = self.root

        q = [] # queue for doing BFS
        q.append(curr)

        while len(q) > 0:
            curr = q.pop(0)
            # print curr node
            print("Node", end=' ')
            if curr.is_word():
                print(curr.c, end='=')
                print()
            else:
                print(curr.c)

            print("Children", end=' ')
            children = curr.children.keys()

            for c in children:
                child = curr.children[c]
                q.append(child)
                print(c, end=' ')
            print()

def get_segmented_string_in_place(trie, string):
    # convert the string to a list
    inp = list(string)
    size = len(inp)

    cursor = 0
    used = 0
    last_word = -1
    space_added = 0

    curr = trie.get_root()

    while cursor < size:
        c = inp[cursor + space_added]

        next_node = curr.get_child(c)

        if next_node is None:

            if last_word is -1:
                print("Error: String has non-dictionary words")
                exit()

            inp.insert(last_word+1, ' ')
            used = last_word+1
            cursor = last_word-space_added

            space_added = space_added+1
            curr = trie.get_root()
            last_word = -1

        else:
            if next_node.is_word():
                last_word = cursor + space_added# ending of the last word

            curr = next_node

        cursor = cursor+1
        # end of while

    print("Space added: %d" % (space_added))
    return "".join(inp)

def get_segmented_string(trie, string):
    result = ''
    size = len(string)

    cursor = 0
    used = 0
    last_word = -1

    curr = trie.get_root()

    while cursor < size:
        c = string[cursor]

        next_node = curr.get_child(c)

        if next_node is None:
            # this path ends here.

            if last_word is -1:
                print("Error: String has non-dictionary words")
                print("Result: %s, C: %d, char: %c, U: %d, LW: %d" % (result, cursor, c, used, last_word))
                exit()

            result = result + string[used:last_word+1] + ' ' # append the found word in the result
            cursor = last_word # rewind the cursor
            used = last_word + 1 # next word starting point
            curr = trie.get_root() # reset the trienode to root
            last_word = -1 # reset
        else:
            if next_node.is_word():
                last_word = cursor
            curr = next_node

        cursor = cursor + 1 # look at the next node

    if last_word is not -1:
        result = result + string[used:last_word+1]

    return result

if __name__ == "__main__":
    args = len(sys.argv)

    '''
    Argument list
        <exe> <string> <dictionary .. list of strings>
    '''

    if args < 3:
        print("Error: Too few arguments")
        print("Usage: ./script <string-to-split> <list of strings of the dictionary>")
        exit()


    string = sys.argv[1]
    dictionary = sys.argv[2:]

    print(string)
    print(dictionary)

    trie = Trie()
    trie.build(dictionary)
    #trie.show()

    split_string = get_segmented_string(trie, string)
    print(split_string)

    split_string2 = get_segmented_string_in_place(trie, string)
    print(split_string2)
