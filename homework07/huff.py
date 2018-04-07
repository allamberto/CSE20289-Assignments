#!/usr/bin/env python3

import os
import string
import sys

if __name__ == '__main__':
    urlList = list()
    response = requests.get('https://www.gutenberg.org/files/1342/1342-pdf.pdf?session_id=a798f059d3dc54813d3316522cb424020e3db481')
    urlList.append(response)
    response = requests.get('https://www.gutenberg.org/files/1342/1342-pdf.pdf?session_id=a798f059d3dc54813d3316522cb424020e3db481')
    urlList.append(response)
    book = response.json()
    for line in book:
        os.popen(huff)
