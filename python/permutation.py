#!/usr/bin/python3

def perm(slate, array):
    if len(array) == 0:
        print ("".join(slate))
    else:
        for i in range(0, len(array)):
            slate.append(array[i])
            perm(slate, array[:i]+array[i+1:])
            slate.pop()
    # End perm

if __name__ == "__main__":
    arr = str(input("Enter a string: "))
    perm([], arr)
