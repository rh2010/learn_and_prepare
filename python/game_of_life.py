#!/usr/bin/python3
import sys

'''
Game Of Life:

'''

class game_of_life:
    def __init__(self):
        pass

    def play(self, board):
        rows = len(board)
        columns = len(board[0])

        if rows is 0 or columns is 0:
            return

        for i in range(rows):
            for j in range(columns):
                self.update_board(board, i, j)

        '''
        Now that all the values are updated, remove the older values.
        '''
        for i in range(rows):
            for j in range(columns):
                board[i][j] = board[i][j] >> 1 # the updated value if in the 2nd bit

    def get_value(self, board, row, column):
        if r < 0 or c < 0 or r == len(board) or c == len(board[0]):
            return 0

        '''
        always return the value in '0'th bit.
        the 1st bit might be non-zero with the update value
        '''
        return board[row][column] & 1

    def update_board(self, board, row, column):
        count = 0

        for r in (-1, 0, 1):
            for c in (-1, 0, 1):
                if r is 0 and c is 0:
                    continue
                count = count + self.get_value(board, row+r, column+c)

        if count is 3:
            board[row][column] = board[row][column] + 2
        elif count is 2:
            board[row][column = board[row][column] * 3
