#!/usr/bin/python

def subset(arr, idx, slate):
    if idx == len(arr):
        print ("%s" % (slate))
        return

    subset(arr, idx+1, slate)
    slate.append(arr[idx])
    subset(arr, idx+1, slate)
    slate.pop()

if __name__ == "__main__":
    s = str(raw_input("Enter: "))
    subset(s, 0, [])
