#!/usr/bin/python3
import sys

'''
Grid Illumination:
Given an NxN grid with an array of lamp  coordinates.
Each lamp provides illumination to every square on their x axis,
every square on their y axis, and every square that lies in their diagonal
(think of a Queen in chess).
Given an array of query coordinates, determine whether that point is illuminated
or not.
The catch is when checking a query all lamps adjacent to, or on, that query get
turned off. The ranges for the variables/arrays were about: 10^3 < N < 10^9, 10^3 < lamps < 10^9, 10^3 < queries < 10^9.
'''

'''
O(n) time and space for processing the board and lamps.
O(1) time for processing the query.
'''
class grid_illumination:
    row = ''
    col = ''
    fwd_diag = ''
    back_diag = ''

    def __init__(self, lamps=None):
        row = set()
        col = set()
        fwd_diag = set()
        back_diag = set()

        if lamps is not None:
            for lamp in lamps:
                self.add_lamp(lamp[0], lamp[1])
        # end of constructor

    def add_lamp(self, i, j):
        '''
        add the row index to the set
        '''
        self.row.add(i)

        '''
        add the column index to the set
        '''
        self.col.add(j)

        '''
        the fwd diagonal is i+j
        '''
        self.fwd_diag.add(i+j)

        '''
        the back diagonal or rev diagonal is i-j
        '''
        self.back_diag.add(i-j)

    def query_spot(i, j):
        if i in self.row:
            return True

        if j in self.col:
            return True

        if i+j in self.fwd_diag:
            return True

        if i-j in self.back_diag:
            return True

        return False

if __name__ == "__main__":
   
    # get the list of lamps
    lamps = []
    gi = grid_illumination(lamps)

    # get the list of queries
    queries = []
    for query in queries:
        print("%s" % (gi.query_spot(query[0], gi.query_spot[1])))
        
