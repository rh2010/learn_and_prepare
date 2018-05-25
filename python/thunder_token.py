#!/usr/bin/python

'''
Time Complexity: O(nlog(height))
Space Complexity: O(n)
'''
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
