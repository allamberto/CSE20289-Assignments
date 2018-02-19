#!/usr/bin/env python3

import os
import sys

# Global Variables

delim="     "

# Usage function

def usage(status=0):
    print('''Usage: {} files...

    -d  DELIM   use DELIM instead of TAB for field delimiter
    -f  FIELDS  select only these fields'''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

# Parse command line options

args = sys.argv[1:]
while args and args[0].startswith('-') and len(args[0]) > 1:
    arg = args.pop(0)
    if arg == '-d':
        delim = args.pop(0)
    elif arg == "-f":
        fields = args.pop(0)
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

b = set(",")
fields.split(",")
fields = set(fields)
fields = fields - b
fields = sorted(fields)
word = ""

for line in stream:
    sepLine = line.split(delim)
    if(len(fields) == 2):
        seq = [sepLine[int(fields[0]) - 1], sepLine[int(fields[1]) - 1]]
        word = ":".join(seq)
    else:
        word = sepLine[int(fields[0]) - 1]
    print(word)
    word = ""
