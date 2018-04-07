#!/usr/bin/env python3

import os
import sys
import yaml

books = ['alice.txt', 'heart_dark.txt', 'pride_pred.txt', 'frank.txt', 'two_city.txt']

print("| {:20}| {:13}| {:13}| {:13}|".format("FILE", "OLD SIZE", "NEW SIZE", "RATIO"))
print("|{:-<21}|{:-<14}|{:-<14}|{:-<14}|".format("-", "-", "-", "-"))

for i in books:
    nSize = 0

    cmd = 'iconv -sc -f utf-8 -t iso-8859-1 ' + i + ' > curr.ascii'
    os.system(cmd)

    ostr = "stat -c '%s' curr.ascii"
    oSize = os.path.getsize('curr.ascii') * 8

    dstr = './huff -f json curr.ascii > curr.new'

    d = yaml.load(os.popen(dstr))

    nSize = os.path.getsize('curr.new') * 32

    ratio = (nSize / oSize) * 100

    print("| {:20}| {:13}| {:13}| {:>12}%|".format(i, oSize, nSize, '%.2f'% ratio)) #formats the output table
