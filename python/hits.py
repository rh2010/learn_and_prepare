#!/usr/bin/python3

import time
import multiprocessing

class hits:
    q = ''
    lock = ''
    def __init__(self):
        self.q = []
        self.lock = multiprocessing.Lock()

    def record(self):
        self.lock.acquire()
        self.q.append(time.time())
        self.lock.release()

    def get():
        '''
        report the number of hits in the last 5 minutes
        '''
        self.lock.acquire()
        while len(q) > 0 and time.time()-q[0] > 300:
            q.pop(0)
        size = len(q)
        self.lock.release()

        return size

    def clean_up(window):
        '''
        clean up entries older than the time window specified
        run it every seond
        '''
        self.lock.acquire()
        while len(q) > 0 and time.time()-q[0] > window:
            q.pop(0)
        self.lock.release()

def cleanup_old(hits_obj, q):
    while True:
        time.sleep(1)
        hits_obj.clean_up()

if __name__ == "__main__":
    h = hits()

    cleanup_thread = multiprocessing.Process(target=cleanup_old, args=(h))
    cleanup_thread.daemon = True
    cleanup_thread.start()

    ....
    cleanup_thread.terminate()

