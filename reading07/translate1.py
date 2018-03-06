#!/usr/bin/env python3

import re

pattern = '9\d*9'
length = [len(re.findall(pattern, row)) for row in open('/etc/passwd') if re.findall(pattern, row)]
print(sum(length))
