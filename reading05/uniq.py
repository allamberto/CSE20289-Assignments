#!/usr/bin/env python3

import os
import sys

# Global Variables

occur = False

# Usage function

def usage(status=0):
    print('''Usage: {} files...

    -c  prefix lines by the number of occurrences'''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

# Parse command line options

args = sys.argv[1:]
while args and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-c':
        occur = True
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if not args:
    args.append('-')

# Main execution

for path in args:
    if path == '-':
        stream = sys.stdin
    else:
        stream = open(path)

names = {}

for line in stream:
    if line not in names:
        names[line] = 1
    else:
        names[line] = names[line] + 1

if occur:
    for key in names:
        line = '{:>7} {:<10}'.format(names[key], key)
        line = line.rstrip()
        print(line)
else:
    for key in names:
        line = key
        line = line.rstrip()
        print(line)
