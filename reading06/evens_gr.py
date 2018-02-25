#!/usr/bin/env python3

import sys

def evens(stream):
    for number in stream:
        number = number.strip()
        if int(number) % 2 == 0:
            yield number

print(' '.join(evens(sys.stdin)))
