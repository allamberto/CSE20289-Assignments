#!/usr/bin/env python3

import re

pattern = '[Uu]ser'
rows = [row.rstrip() for row in open('/etc/passwd')]
rows = map(lambda s: s.split(':'), rows)
five = [row[4] for row in rows]
result = [word for word in five if re.findall(pattern, word)]
print(len(result))
