#!/usr/bin/python3
# 
# URL Traversal : A Naive example.
#
from urllib.request import urlopen
import ssl
from bs4 import BeautifulSoup
import re

def followLink(url, ctx, index):
    print("Opening: %s" % (url))

    name = re.findall('known_by_(.+)\.', url)[0]
    html = urlopen(url, context=ctx).read()
    soup = BeautifulSoup(html, 'html.parser')
    
    # Retrive all tags
    tags = soup('a')

    if index > len(tags):
        print("Index out of range")
        return None

    link = tags[index].get('href', None)
    #print("Name: %s" % (name))

    return link, name
    # End of follow link

sslctx = ssl.create_default_context()
sslctx.check_hostname = False
sslctx.verify_mode = ssl.CERT_NONE

url = input('Enter url - ')
count = int(input('Count: '))
index = int(input('Position: '))

print("Url: %s" % (url))
print("count: %d" % (count))
print("index: %d\n\n" % (index))

if index <= 0:
    print("Index value %d, should be greater than 0." % (index))
    exit()
#
#
#
for i in range(0, count+1):
    print("loop: %d" % (i+1))
    url, name = followLink(url, sslctx, index-1)

    if url is None:
        print("Ending loop at %d" % (i))

print("%s" % (name))

