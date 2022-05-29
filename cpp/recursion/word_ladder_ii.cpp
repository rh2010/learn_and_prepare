class Solution {
    
    /*
        This is effectively doing a DFS, hence, isn't optimal.
        TBD: Performing a BFS would be faster. 
    */
    void helper(string beginWord, string endWord, vector<string>& wordList, vector<string> &slate, vector<vector<string>> &result) {

        string lastWord = slate[slate.size()-1];
        
        if (lastWord == endWord) {
            // result found
            printf("Result found size (%d).\n", slate.size());
            if (result.size() == 0) {
                printf("\t Adding size: %d\n", slate.size());
                result.push_back(slate);
            } else {
                // if the current found solution
                while (result.size() > 0) {
                    if (slate.size() < result[result.size()-1].size()) {
                        printf("\tRemoving, last-size: (%d).\n", result[result.size()-1].size());
                        result.pop_back();
                    } else if (slate.size() == result[result.size()-1].size()) {
                        printf("\tlast: (%d), curr: (%d).\n", result[result.size()-1].size(), slate.size());
                        result.push_back(slate);
                        return;
                    }
                }
                
                // if all the solutions so far were longer than current found solution,
                // all of the them would have been removed.
                if (result.size() == 0) {
                    printf("Adding size: %d\n", slate.size());
                    result.push_back(slate);
                }
            }
            return;
        }
        
        if ((result.size() > 0) && (slate.size() >= result[result.size()-1].size()) ) {
            printf("Backtrack: LastResult: (%d), Slate: (%d)\n", result[result.size()-1].size(), slate.size());
            return;   
        }

        // base case
        if (wordList.size() == 0) {
            return;
        }

        unordered_map<string, int> adjacent;
        // find Adjacent
        //printf("Building Adjacent for (%s): ", lastWord.c_str());
        for (int i = 0; i < wordList.size(); i++) {
            string curr(wordList[i]);
            
            int diff = 0;
            //if (beginWord == curr) {
                //printf("\tSkipping begin Word: (%s:%d)\n", curr.c_str(), i);
                //continue;
            //}
            for (int wIdx = 0; wIdx < curr.size(); wIdx++) {
                if (lastWord[wIdx] != curr[wIdx]) {
                    ++diff;
                }
                if (diff > 1) {
                    continue;
                }
            }
            if (diff < 2) {
                adjacent.insert({curr, i});
                //printf("(%s:%d, %d),", curr.c_str(), i, diff);
            }
        }
        //printf("\n");
        
        if (adjacent.size() == 0) {
            // nothing to go on
            return;
        }
        
        // recursion
        for (auto it = adjacent.begin(); it != adjacent.end(); it++) {
            slate.push_back(it->first);
            wordList.erase(wordList.begin()+it->second);
            
            helper(beginWord, endWord, wordList, slate, result);
            
            wordList.insert(wordList.begin()+it->second, it->first);
            slate.pop_back();
        }
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> result;
        vector<string> slate;
        
        slate.push_back(beginWord);
        
        for (auto it = wordList.begin(); it != wordList.end(); it++) {
            if (*it == beginWord) {
                wordList.erase(it);
                break;
            }
        }
        helper(beginWord, endWord, wordList, slate, result);
        return result;
    }
};
