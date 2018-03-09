#!/usr/bin/env python3

import requests
import sys
import os

ids = []
lines = requests.get('http://yld.me/raw/lmz').text.splitlines()
ids = [line.split(',') for line in lines]
ids = sorted(ids, key=lambda n: n[3])
names = [i[0] for i in ids]
result = [name.upper() for name in names]
for n in result:
    print(n)
