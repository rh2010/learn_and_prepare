#include <iostream>
#include <cstdlib>
#include <cstring>

#define RED 'R'
#define GREEN 'G'
#define BLUE 'B'

void swap(vector<char> &balls, int idx1, int idx2) {
    char temp = balls[idx2];
    balls[idx2] = balls[idx1];
    balls[idx1] = temp;
}

vector<char> dutch_flag_sort(vector<char> &balls) {
    // Write your code here.
    int redPtr = -1;
    int greenPtr = -1;
    
    for (int bluePtr = 0; bluePtr < balls.size(); bluePtr++) {
        if (balls[bluePtr] == GREEN) {
            swap(balls, ++greenPtr, bluePtr);
        } else if (balls[bluePtr] == RED) {
            swap(balls, ++redPtr, bluePtr);
            if (balls[bluePtr] == GREEN) {
                swap(balls, ++greenPtr, bluePtr);
            } else {
                ++greenPtr;
            }
        }
    }
    
    return balls;
}

