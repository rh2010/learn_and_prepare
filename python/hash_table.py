#!/usr/bin/python3
'''
Implement a concurrent hash-table
'''
class entry:
    key = None
    value = None
    h = None

    def __init__(self, key, value, h):
        self.key = key
        self.value = value
        self.h = h

class hashTable:
    capacity = None
    loadFactor = None
    table = None
    threshold = None

    def __init__(self, c=16, lf=0.75):

        if c < 16:
            c = 16
            
        self.capacity = c
        self.loadFactor = lf
        self.table = [[]] * self.capacity
        self.threshold = self.capacity * self.loadFactor

    def get(self, key):
        # find the element with 'key'
        if key is None:
            return None

        h = self.hash(key)
        index = self.get_index(h)
        l = table[index]

        for e in l:
            if e.h == h and e.key == key:
                return e.value

        return None

    def put(self, key, value):
        # add an element with 'key' and 'value' to the table
        if key is None
            return None

        h = self.hash(key)
        index = self.get_index(h)
        l = table[index]

        for e in l:
            if e.hash == h and e.key == key:
                old_value = e.value
                e.value = value
                return old_value

        e = entry(key, value, h)
        l.append(e)

        self.size += 1

        if self.size >= self.threshold:
            self.resize()

    def resize(self):
        # the load factor of the table has gone beyond the threshold
        # of loadFactor, re-size the table to twice the size.
        #
        self.capacity = 2 * self.capacity
        self.threshold = new_capacity * self.loadFactor
        new_table = [[]] * new_capacity

        for i in range(len(self.table)):
            l = table[i]
            for e in l:
                index = self.get_index(e.hash)
                l2 = new_table[index]
                l2.append(e)

        del self.table
        self.table = new_table

    def hash(self, key):
        # for the given 'key' calculate the hash-value
        # of the 'key'
        # for integers we can use an integer hashing function from a universal family
        '''
        hashing for intergers
    
        h = (a*key + b)%p
        p is a prime number bigger than key
        a is betweek 1 and p-1
        b is between 0 and p-1
        '''

        '''
        for strings we can use a universal hashing function as well

        eg:

        h = 0
        x = 31
        p .. a big prime number
        for c in string:
            h = (h*x + a) mod p

        use every character in the string for calculating the hash function 
        '''
    def get_index(self, h):
        return h%self.capacity



class concurrentHashTable:
    '''
    for concurrent hash table
    we need a read-write lock to guard access each bucket

    if we have a lock per bucket, then it will be massively concurrent but,
    it will also use a lot of memory.

    we need to set how much concurrency we need.
    as in how many threads are expected to access the hash-table in parallel
    '''
    capacity = None
    load_factor = None
    size = None
    table = None # hash-table
    concurrency = None
    locks = None # array of locks
    resizeLock = None

    def __init__(self, c=16, concurrency=4):
        if c < 16:
            c = 16

        if concurrency < 4:
            concurrency = 4

        self.capacity = c
        self.concurrency = concurrency
        self.load_factor = 0.6
        self.threshold = int(self.capacity*self.load_factor)
        self.table = [[]] * self.capacity
        self.locks = rwLocks() * self.concurrency
        self.resizeLock = threading.Lock()

    def get_index(self, h):
        '''
        return in index of table and lock_index as well
        '''
        table_index = h % self.capacity
        lock_index = h / self.concurrency

        return table_index, lock_index

    def get(self, key):
        # find the element with 'key'
        if key is None:
            return None

        h = self.hash(key)
        index, lock_index = self.get_index(h)

        rwLock = self.locks[lock_index]

        read_lock(rwLock)
        l = table[index]

        for e in l:
            if e.h == h and e.key == key:
                value = e.value
                write_unlock()
                return value

        read_unlock(rwLock)

        return None

    def update_size(self):
        with self.resizeLock:
            self.size += 1
            if self.size >= self.threshold:
                self.resize()

    def put(self, key, value):
        # add an element with 'key' and 'value' to the table
        if key is None
            return None

        h = self.hash(key)
        index, lock_index = self.get_index(h)
        rwLock = self.locks[lock_index]

        write_lock(rwLock)
        l = table[index]

        for e in l:
            if e.hash == h and e.key == key:
                old_value = e.value
                e.value = value
                write_unlock(rwLock)

                return old_value

        e = entry(key, value, h)
        l.append(e)
        write_unlock(rwLock)
        self.update_size()

    def get(self, key):

    def put(self, key, value):

    def resize(self):
        '''
        this should be the same as the resize operation in class hashTable
        the only change will be 
        lock(resizeLock)
            ... do work same as resize of class hashTable
        unlock(resizeLock)
        '''

    def hash(self, key):
        '''
        same the the hash for class hashTable
        '''
