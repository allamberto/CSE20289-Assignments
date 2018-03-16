#!/usr/bin/env python3

import os
import sys

# Usage function

def usage(status=0):
    print('''Usage: {} files...

    -r  reverse the result of comparisons'''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)


choice = False

# Parse command line options

args = sys.argv[1:]
while args and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-r':
        choice = True
    elif arg == '-h':
        usage(0)
    else:
        usage(1)

if len(args) == 0:
    args.append('-')

# Main execution

for path in args:
    if path == '-':
        stream = sys.stdin
    else:
        stream = open(path)

stream = sorted(stream, reverse = choice)
for line in stream:
    line = line.rstrip()
    print(line)
