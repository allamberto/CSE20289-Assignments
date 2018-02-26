#!/usr/bin/env python3

import sys

print(' '.join([number.strip() for number in sys.stdin if int(number) % 2 == 0]))
