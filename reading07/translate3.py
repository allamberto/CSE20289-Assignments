#!/usr/bin/env python3

import re
import requests

pattern = '^B.*'
lines = requests.get('http://yld.me/raw/lmz').text.splitlines()
lines = map(lambda s: s.split(','), lines)
second = [line[1] for line in lines]
result = [word for word in second if re.findall(pattern, word)]
for name in sorted(result):
    print(name)
