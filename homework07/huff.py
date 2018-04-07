#!/usr/bin/env python3

import os
import sys
import yaml

books = ['monte_cristo.txt', 'beowulf.txt', 'les_mis.txt', 'frankenstein.txt', 'iliad.txt']

print("| {:20}| {:13}| {:13}| {:13}|".format("FILE", "OLD SIZE", "NEW SIZE", "RATIO"))
print("|{:-<21}|{:-<14}|{:-<14}|{:-<14}|".format("-", "-", "-", "-"))

for i in books:
    nSize = 0

    cmd = 'iconv -sc -f utf-8 -t iso-8859-1 ' + i + ' > curr.ascii'
    os.system(cmd)

    ostr = "stat -c '%s' curr.ascii"
    oSize = os.path.getsize('curr.ascii')

    #oSize = int((os.popen(ostr).read())) * 8

    dstr = './huff -f json curr.ascii'

    d = yaml.load(os.popen(dstr))

    print(d)

    for key in d:
        nSize += len(d[key]['encoding']) * int(d[key]['count'])

    ratio = (nSize / oSize) * 100

    print("| {:20}| {:13}| {:13}| {:i>12}%|".format(i, oSize, nSize, '%.2f'% ratio))
