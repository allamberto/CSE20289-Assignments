#!/usr/bin/env python3

import sys
import os.path

if sys.argv == 0:
    print ("Usage: exists.sh file0...")
    sys.exit(1)

exitCode = 0

for arg in sys.argv[1:]:
    if os.path.isfile(arg):
        print(arg + "exists")
    else:
        print (arg + "does not exist")
        exitCode = 1


sys.exit(exitCode)
