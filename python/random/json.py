#!/usr/bin/python3
#
# Parsing a JSON file from python : A Basic Example
#
import json

data = '''[
    {
        "id" : "007",
        "x" : "2",
        "name" : "Chuck"
    },
    {
        "id" : "009",
        "x" : "7",
        "name" : "Chuck"
    }
]'''

info = json.loads(data)

print("Type: %s, Count: %d" % (type(info), len(info)))

for item in info:
    print('Name:', item["name"])
    print('Id:', item["id"])
