#!/usr/bin/env python3

import re
import sys
import os

lines = os.popen('/bin/ls -l /etc').read().splitlines()
rows = [row.rstrip() for row in lines]
rows = map(lambda s: s.split(), rows)
nums = [row[1] for row in rows]
count = {}
sortNums = sorted(nums)
for num in sortNums:
    if num in count.keys():
        count[num] = count[num] + 1
    else:
        count[num] = 1
for key, val in count.items():
    print(('{:>7} {}').format(val, key))
