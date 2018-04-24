#include <iostream>

using namespace std;

/*
 * Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 *
 * Example:
 *  Input: [100, 4, 200, 1, 3, 2]
 *  Output: 4
 *  Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
 */

int longestConsecutive(vector<int>& nums)
{
    unordered_map <int, int> hash_table;
            
    // insert into the hash_table
    for (int i=0; i < nums.size(); i++) {
        hash_table.insert({nums[i], i});
    }
    int max_count = 0;
    
    for (int i=0; i<nums.size(); i++) {
        if (hash_table.find(nums[i]-1) == hash_table.end()) {
            // prev not found
            // this is the first element in the sequence
            int count = 0;
            int temp = nums[i];
            while (hash_table.find(temp) != hash_table.end()) {
                count++;
                temp++;
            }
            // update max_count
            if (count > max_count) {
                max_count = count;
            }
        }
    } // end for loop
    return max_count;
}
