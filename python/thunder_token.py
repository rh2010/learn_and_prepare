#!/usr/bin/python

'''
Time Complexity: O(nlog(height))
Space Complexity: O(n)
'''
def longestChain(block_list):
    level = [-1] * len(block_list)


    print("longestChain")
    #print(block_list)
    #print(level)

    for idx, block in enumerate(block_list):
        stack = []
        p = idx
        while p != -1:
            if level[p] == -1:
                stack.append(p)
            else:
                break
            p = block_list[p]

        l = 0
        if p == -1:
            l = 0
        else:
            l = level[p]

        while len(stack) > 0:
            p = stack.pop()
            l += 1
            level[p] = l
        del stack
        #print(level)

    #print(level)

    max_level = -1
    max_level_index = -1

    for i,l in enumerate(level):
        if l > max_level:
            max_level = l
            max_level_index = i

    #print(max_level, max_level_index)

    idx = max_level_index
    result = []
    while idx != -1:
        result.append(idx)
        idx = block_list[idx]

    result.reverse()

    return result

def find_longest_chain(block_list):
    level = [0] * len(block_list) # array to hold the level for each block

    print("level:\n\t%s" % (level))
    for idx,block in enumerate(block_list):
        depth = 1
        if block is -1:
            depth = 0
        else:
            if block < idx:
                depth = 1 + level[block]
        level[idx] = depth

    print("level after 1st pass:\n\t%s" % (level))

    done = False
    max_level = 0
    index_max_level = -1

    loops = 0
    # this loop should terminate in log(height) runs.
    while not done:
        loops += 1
        done = True
        for idx,block in enumerate(block_list):
            if block is -1:
                depth = 0
            else:
                depth = 1+level[block]
            if level[idx] != depth:
                done = False
                level[idx] = depth
            if max_level < depth:
                max_level = depth
                index_max_level = idx
        print("\t[%d] %s" % (loops, level))

    print("Stats:")
    print("\tLoops: %d" % (loops))
    print("\tmax_level: %d" % (max_level))
    print("\tBlock at max level: %d" % (index_max_level))

    result = []
    idx = index_max_level
    while idx != -1:
        result.append(idx)
        idx = block_list[idx]

    result.reverse()
    return result

if __name__ == "__main__":

    block_list = [6,7,1,2,2,1,5,-1,0,5]

    longest_path = find_longest_chain(block_list)
    print(longest_path)
    longest_path = longestChain(block_list)
    print(longest_path)
