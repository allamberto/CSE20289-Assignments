#!/usr/bin/env python3

import os
import sys

grab = []
lines = [line.rstrip() for line in open('/etc/passwd')]
grab = [line.split(':')[6] for line in lines]
results = set(grab)
print(len(sorted(results)))
