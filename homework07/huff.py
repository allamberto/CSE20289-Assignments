#!/usr/bin/env python3

import os
import sys
import yaml

scripts = ['alice.txt', 'heart_dark.txt', 'pride_pred.txt', 'wilde.txt', 'grime.txt']

print("| {:20}| {:13}| {:13}| {:13}|".format("FILE", "OLD SIZE", "NEW SIZE", "RATIO"))
print("|{:-<21}|{:-<14}|{:-<14}|{:-<14}|".format("-", "-", "-", "-"))

for i in scripts:
    nSize = 0

    cmd = 'iconv -sc -f utf-8 -t iso-8859-1 ' + i + ' > curr.ascii'
    os.system(cmd)

    oSize = os.path.getsize('curr.ascii') * 8

    d = yaml.load(os.popen('./huff -f json curr.ascii'))
    for char in d:
        nSize += len(d[char]['encoding']) * int(d[char]['count'])

    ratio = (nSize / oSize) * 100

    print("| {:20}| {:13}| {:13}| {:>12}%|".format(i, oSize, nSize, '%.2f'% ratio)) #formats the output table
