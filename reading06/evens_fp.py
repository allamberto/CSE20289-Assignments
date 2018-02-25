#!/usr/bin/env python3

import sys

print(' '.join(list(filter(lambda a: int(a) % 2 == 0, map(lambda str: str.strip(), sys.stdin)))))
